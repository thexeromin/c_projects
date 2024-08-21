#include <ncurses.h>
#include <string.h>
#include <stddef.h>

#include "./library.h"
#include "./window.h"

#define MAX_LEN 50
#define TOTAL_MSG 10

void print_messages(WINDOW* win);

static char messages[TOTAL_MSG][MAX_LEN];
static int top = 0;     // tract empty spot in messages

int main(void) {
    WINDOW* msg_win;
    char msg_input[MAX_LEN];
    wchar_t c;

    // initialize curses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    // create window for message display
    msg_win = create_newwin(
        LINES - 4,
        COLS - 2,
        1,
        1, 
        "Message Window"
    );
    refresh();

    while(1) {
        c = wgetch(msg_win);

        // quite if q pressed
        if(c == 'q') break;

        switch(c) {
        case '/':
            echo();
            mvwgetstr(stdscr, LINES - 1, 1, msg_input);
            strcpy(messages[top++], msg_input);
            clrtoeol();
            noecho();
            break;
        }

        print_messages(msg_win);
    }

    clrtoeol();
    refresh();
    endwin();

    return 0;
}

void print_messages(WINDOW* win) {
    int x = 2, y = 4;

    for(int i = 0; i < top; i++) {
        mvwprintw(win, y, x, "%s", messages[i]);
        ++y;
    }
    wrefresh(win);
}
