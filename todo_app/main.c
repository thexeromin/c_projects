#include <ncurses.h>
#include <string.h>
#include <stddef.h>

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
void print_help_menu(
    WINDOW* win
);
void print_in_middle(
    WINDOW* win,
    int starty,
    int startx,
    int width, 
    char* string,
    chtype color
);
void print_menu(WINDOW *menu_win, int highlight);

char* menu_options[] = {
    "[i] Add todo",
    "[j] Move down [k] Move up",
    "[q] Quit",
};
int menu_options_length = sizeof(menu_options) / sizeof(menu_options[0]);
char todos[100][10];
int curr_idx = 0;
int n_todos = sizeof(todos) / sizeof(char *);

int main() {
    WINDOW* info_win;
    WINDOW* view_win;

    int highlight = 1;
    int choice = 0;
    wchar_t c;

    char input_str[100];

    // initialize curses
    initscr();
    start_color();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    // Initialize all the colors
	init_pair(1, COLOR_CYAN, COLOR_BLACK);

    info_win = create_newwin(INFO_WIN_HEIGHT, COLS - 4, 2, 2, "COMMANDS", 1);
    view_win = create_newwin(LINES - (INFO_WIN_HEIGHT + 10), COLS - 4, 2 + INFO_WIN_HEIGHT, 2, "TODOS", 1);

    refresh();

    print_help_menu(info_win);
    print_menu(view_win, highlight);

    while(1) {	
        c = wgetch(view_win);
		switch(c) {
            case 'k':
				if(highlight == 1)
					highlight = n_todos;
				else
					--highlight;
				break;
			case 'j':
				if(highlight == n_todos)
					highlight = 1;
				else 
					++highlight;
				break;
            case 'i':
                echo();
                mvwgetstr(stdscr, LINES - 2, 1, input_str);
                strcpy(todos[curr_idx++], input_str);
                noecho();
                break;
            case 'q':
				choice = highlight;
                break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		}
		print_menu(view_win, highlight);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}	

    clrtoeol();
    refresh();
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

void print_help_menu(
    WINDOW* win
) {
    int width, height;

    getmaxyx(win, height, width);

    for(int i = 0; i < menu_options_length; i++) {
        mvwprintw(win, 3 + i, 2, "%s", menu_options[i]);
    }

    wrefresh(win);
}

void print_menu(WINDOW *menu_win, int highlight) {
	int x, y, i;	

	x = 2;
	y = 3;
	box(menu_win, 0, 0);
	for(i = 0; i < curr_idx; ++i) {
        if(highlight == i + 1) { /* Hightlight the present choice */ 
            wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", todos[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", todos[i]);
		++y;
	}
	wrefresh(menu_win);
}
