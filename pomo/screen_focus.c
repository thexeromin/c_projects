#include <stdio.h>

#include "raylib.h"
#include "library.h"
#include "screens.h"

// Module Variables Definition (local)
static Timer focusTimer = { 0 };
static float maxFocusTime = 1800;
static char value[50];

// Focus Screen Initialization logic
void InitFocusScreen(void) {
    StartTimer(&focusTimer, maxFocusTime);
}

// Focus Screen Update logic
void UpdateFocusScreen(void) {
    UpdateTimer(&focusTimer);
    sprintf(
        value,
        "%02.0f:%02d:%02d",
        focusTimer.lifetime / 3600,
        (int) (focusTimer.lifetime / 60) % 60,
        (int) focusTimer.lifetime % 60
    );
}

// Focus Screen Draw logic
void DrawFocusScreen(void) {
    ClearBackground((Color) {186, 73, 73, 0});

    DrawText(
        value,
        (GetScreenWidth() / 2) - 100,
        100,
        65,
        WHITE
    );
}

// Focus Screen Unload logic
void UnloadFocusScreen(void) {
    // Unload LOGO screen variables here!
}

// Focus Screen should finish?
int FinishFocusScreen(void) {
    return 0;
}
