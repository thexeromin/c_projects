#include <ncurses.h>

#ifndef WINDOW_H
#define WINDOW_H

WINDOW* create_newwin(
    int height,
    int width,
    int starty,
    int startx,
    char* label
);
void win_show(WINDOW* win, char* label);
void print_in_middle(
    WINDOW* win,
    int starty,
    int startx,
    int width, 
    char* string
);

#endif // WINDOW_H
