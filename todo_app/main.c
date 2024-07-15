#include <ncurses.h>
#include <string.h>

#define INFO_WIN_HEIGHT 7

WINDOW* create_newwin(
    int height,
    int width,
    int starty,
    int startx,
    char* label,
    int label_color
);
void win_show(WINDOW* win, char* label, int label_color);
void print_in_middle(
    WINDOW* win,
    int starty,
    int startx,
    int width, 
    char* string,
    chtype color
);

int main() {
    WINDOW* info_win;
    WINDOW* view_win;

    // initialize curses
    initscr();
    start_color();
    cbreak();
    keypad(stdscr, TRUE);

    // Initialize all the colors
	init_pair(1, COLOR_CYAN, COLOR_BLACK);

    refresh();

    info_win = create_newwin(INFO_WIN_HEIGHT, COLS - 4, 2, 2, "COMMANDS", 1);
    view_win = create_newwin(LINES - (INFO_WIN_HEIGHT + 10), COLS - 4, 2 + INFO_WIN_HEIGHT, 2, "TODOS", 1);

    getch();
    endwin();
    return 0;
}

WINDOW* create_newwin(
    int height,
    int width,
    int starty,
    int startx,
    char* label,
    int label_color
) {
    WINDOW* local_win;

    local_win = newwin(height, width, starty, startx);

    win_show(local_win, label, label_color);

    wrefresh(local_win);

    return local_win;
}

// Show the window with a border and a label
void win_show(WINDOW* win, char* label, int label_color) {
    int startx, starty, height, width;

	getbegyx(win, starty, startx);
	getmaxyx(win, height, width);

	box(win, 0, 0);
	mvwaddch(win, 2, 0, ACS_LTEE); 
	mvwhline(win, 2, 1, ACS_HLINE, width - 2); 
	mvwaddch(win, 2, width - 1, ACS_RTEE); 
	
	print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}


void print_in_middle(
    WINDOW* win,
    int starty,
    int startx,
    int width, 
    char* string,
    chtype color
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
    wattron(win, color);
    mvwprintw(win, y, x, "%s", string);
    wattroff(win, color);
    refresh();
}