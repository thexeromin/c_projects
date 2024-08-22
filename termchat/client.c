#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <threads.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "./library.h"
#include "./window.h"

#define MAX_LEN 50
#define TOTAL_MSG 10
#define MAXDATASIZE 100 // max number of bytes we can get at once
#define PORT "3490"

void *get_in_addr(struct sockaddr *sa);

// Shared data between threads
typedef struct {
    char messages[TOTAL_MSG][MAX_LEN];
    int top;
    int sockfd;
    mtx_t mutex;
} SharedData;

void print_messages(WINDOW* win, SharedData *data);
int thread_func(void* arg);

int main(int argc, char *argv[]) {
    WINDOW* msg_win;
    char msg_input[MAX_LEN];
    wchar_t c;

    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;

    thrd_t thread;
    SharedData shared_data;

    // init mutex
    mtx_init(&shared_data.mutex, mtx_plain);

    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    // initialize curses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    // initialize socket
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    freeaddrinfo(servinfo); // all done with this structure

    // create window for message display
    msg_win = create_newwin(
        LINES - 4,
        COLS - 2,
        1,
        1, 
        "Message Window"
    );
    refresh();
    nodelay(msg_win, TRUE);

    // thread for receiving incoming messages from server
    shared_data.top = 0;
    shared_data.sockfd = sockfd;
    thrd_create(&thread, thread_func, &shared_data);

    while(1) {
        c = wgetch(msg_win);

        if(c == 'q') break;

        print_messages(msg_win, &shared_data);

        switch(c) {
        case '/':
            echo();
            mvwgetstr(stdscr, LINES - 1, 1, msg_input);

            // send message to server
            if(send(sockfd, msg_input, strlen(msg_input)+1, 0) == -1)
                perror("send");
            clrtoeol();
            noecho();
            break;
        }

    }
    
    mtx_destroy(&shared_data.mutex);

    clrtoeol();
    refresh();
    endwin();

    return 0;
}

void print_messages(WINDOW* win, SharedData *data) {
    int x = 4, y = 4;

    for(int i = 0; i < data->top; i++) {
        mvwprintw(win, y, x, "%s", data->messages[i]);
        ++y;
    }
    wrefresh(win);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int thread_func(void* arg) {
    SharedData* data = (SharedData*)arg;
    int numbytes;
    char buf[MAXDATASIZE];
 
    while(1) {
        if ((numbytes = recv(data->sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
            perror("recv");
            exit(1);
        }

        buf[numbytes] = '\0';
        if(numbytes > 0) {
            mtx_lock(&data->mutex);
            strcpy(data->messages[data->top++], buf);
            mtx_unlock(&data->mutex);
        }
    }
}