#include <stdio.h>
#include <string.h>

#include "library.h"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("error: arguments missing!\n");
        return -1;
    }

    if(strcmp(argv[1], "focus") == 0)
        init_focus();
    else if(strcmp(argv[1], "break") == 0)
        init_break();
    else if(strcmp(argv[1], "help") == 0)
        init_help();
    else if(strcmp(argv[1], "cleanup") == 0)
        cleanup();
    else
        printf("error: %s is not a valid command!\n", argv[1]);

    return 0;
}
