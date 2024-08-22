#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <threads.h>
#include <sys/mman.h>

#define PORT "3490"         // the port user will be connecting to
#define BACKLOG 10          // how many pending connection queue will hold
#define MAXCLIENTS 2        // number of clients can chat
#define MAXDATASIZE 100     // max data size

void sigchld_handler(int s);
void *get_in_addr(struct sockaddr *sa);

// Shared data between threads
typedef struct {
    int clients[MAXCLIENTS];
    int recv_sockfd;
    mtx_t mutex;
} SharedData;

void init_shared_data(SharedData* data);
int thread_func(void* arg);

int main(void) {
    int sock_fd, new_fd;     // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr;      // connectors address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    thrd_t threads[2];
    int curr_thrd = 0;
    int client_idx = 0;
    SharedData shared_data;

    // initalize mutex
    init_shared_data(&shared_data);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;    // use my IP
    
    if((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if((sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if(bind(sock_fd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sock_fd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo);     // all done with this struct
    
    if(p == NULL) {
        fprintf(stderr, "server: faild to bind\n");
        exit(1);
    }

    if(listen(sock_fd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if(sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sock_fd, (struct sockaddr *)&their_addr, &sin_size);
        if(new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(
            their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s,
            sizeof s
        );
        printf("server: got connection from %s - %d\n", s, new_fd);

        // create thread & pass data
        shared_data.recv_sockfd = new_fd;
        shared_data.clients[client_idx++] = new_fd;
        thrd_create(&threads[curr_thrd++], thread_func, &shared_data);
        // thrd_detach(threads[curr_thrd]);
    }

    printf("closing connection\n");
    mtx_destroy(&shared_data.mutex);
    close(sock_fd);

    return 0;
}

void sigchld_handler(int s) {
    (void)s;

    // waitpid() might overwrite errno, so save it
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6
void *get_in_addr(struct sockaddr *sa) {
    if(sa->sa_family == AF_INET) 
        return &(((struct sockaddr_in*)sa)->sin_addr);

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void init_shared_data(SharedData* data) {
    mtx_init(&data->mutex, mtx_plain);
}

int thread_func(void* arg) {
    SharedData* data = (SharedData*)arg;
    int numbytes;
    char buf[MAXDATASIZE];
    int sockfd = data->recv_sockfd;

    // infinite loop for checking messages
    while(1) {
        if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
            perror("recv");
            exit(1);
        }
        if(numbytes > 0) {
            mtx_lock(&data->mutex);
            for(int i = 0; i < 2; i++)  {
                if(data->clients[i] != sockfd) {
                    if(send(data->clients[i], buf, numbytes+1, 0) == -1) {
                        perror("send");
                        mtx_unlock(&data->mutex);
                    }
                }
            }
            mtx_unlock(&data->mutex);
        }
    }

    return 0;
}