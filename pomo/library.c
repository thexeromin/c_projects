#include <stdio.h>
#include <time.h>

static const time_t MAX_FOCUS_TIME = 1500;
static const time_t MAX_BREAK_TIME = 300;

// disable terminal cursor
static void disable_cursor() {
    printf("\e[?25l");
}

// enable terminal cursor
static void enable_cursor() {
    printf("\e[?25h");
}

static void time_loop(time_t max, char* msg) {
    time_t curr_time = time(0);
    time_t start_time = time(0);
    
    disable_cursor();
    while(1) {
        time(&curr_time);
        printf("%2ld\r", curr_time - start_time);
        if((curr_time - start_time) >= max) break;
    }

    printf("%s\n", msg);

    enable_cursor();
}

void init_focus() {
    time_loop(
        MAX_FOCUS_TIME,
        "Awesome master, take a break now!"
    );
}

void init_break() {
    time_loop(
        MAX_BREAK_TIME,
        "Now we need to focus master!"
    );
}

void init_help() {
    printf("Commands:\n");
    printf("pomo focus - to start focus timer\n");
    printf("pomo break - to start break timer\n");
    printf("pomo cleanup - to cleanup\n");
    printf("pomo help  - to print the help menu\n");
}

void cleanup() {
    enable_cursor();
}

