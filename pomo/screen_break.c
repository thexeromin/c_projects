#include <stdio.h>

#include "raylib.h"
#include "library.h"
#include "screens.h"

// Module Variables Definition (local)
static Timer focusTimer = { 0 };
static float maxBreakTime = 300;
static char value[50];

// Break Screen Initialization logic
void InitBreakScreen(void) {
    StartTimer(&focusTimer, maxBreakTime);
}

// Break Screen Update logic
void UpdateBreakScreen(void) {
    UpdateTimer(&focusTimer);
    sprintf(
        value,
        "%02.0f:%02d:%02d",
        focusTimer.lifetime / 3600,
        (int) (focusTimer.lifetime / 60) % 60,
        (int) focusTimer.lifetime % 60
    );
}

// Break Screen Draw logic
void DrawBreakScreen(void) {
    ClearBackground((Color) {56, 133, 138, 0});

    DrawText(
        value,
        (GetScreenWidth() / 2) - 100,
        100,
        65,
        WHITE
    );
}

// Break Screen Unload logic
void UnloadBreakScreen(void) {
    // Unload LOGO screen variables here!
}

// Break Screen should finish?
int FinishBreakScreen(void) {
    return 0;
}
