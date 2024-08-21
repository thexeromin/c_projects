#include <ncurses.h>
#include <string.h>

#include "./window.h"

// create window
WINDOW* create_newwin(
    int height,
    int width,
    int starty,
    int startx,
    char* label
) {
    WINDOW* local_win;

    local_win = newwin(height, width, starty, startx);

    win_show(local_win, label);

    wrefresh(local_win);

    return local_win;
}

// show the window with a border and a label
void win_show(WINDOW* win, char* label) {
    int height, width;

	getmaxyx(win, height, width);
    (void)height;

	box(win, 0, 0);
	mvwaddch(win, 2, 0, ACS_LTEE); 
	mvwhline(win, 2, 1, ACS_HLINE, width - 2); 
	mvwaddch(win, 2, width - 1, ACS_RTEE); 
	
	print_in_middle(win, 1, 0, width, label);
}

// print window label in middle
void print_in_middle(
    WINDOW* win,
    int starty,
    int startx,
    int width, 
    char* string
) {
    int length, x, y;
    float temp;

    if(win == NULL)
        win = stdscr;
    getyx(win, y, x);
    if(startx != 0)
        x = startx;
    if(starty != 0)
        y = starty;
    if(width == 0)
        width = 80;

    length = strlen(string);
    temp = (width - length)/ 2;
    x = startx + (int)temp;
    mvwprintw(win, y, x, "%s", string);
    refresh();
}