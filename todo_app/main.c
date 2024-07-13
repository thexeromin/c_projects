#include <ncurses.h>

#define MAXLEN 100

int main() {
    char value[MAXLEN];
    int line_number = 2;
    int ch;

    initscr();
    cbreak();

    keypad(stdscr, TRUE);

    printw("Press F1 to exit");
    refresh();
    noecho();

    while((ch = getch()) != KEY_F(1)) {
        move(LINES - 1, 0);
        clrtoeol();
        switch(ch) {
            case 'i':
                echo();
                mvprintw(LINES - 1, 0, ": ");
                getstr(value);
                mvprintw(++line_number, 0, "%s", value);
                break;
        }
    }
    endwin();
    return 0;
}
