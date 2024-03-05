#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "library.h"
#include "screens.h"

// Module Variables Definition (local)
static Timer timer = { 0 };
static float maxBreakTime = 300;
static char value[50];
static bool isFinished = false;
static char* msg = "Time to focus!";

// Break Screen Initialization logic
void InitBreakScreen(void) {
    StartTimer(&timer, maxBreakTime);
}

// Break Screen Update logic
void UpdateBreakScreen(void) {
    if(timer.lifetime <= 0) {
        isFinished = true;
    } else {
        UpdateTimer(&timer);
        sprintf(
            value,
            "%02.0f:%02d:%02d",
            timer.lifetime / 3600,
            (int) (timer.lifetime / 60) % 60,
            (int) timer.lifetime % 60
        );
    }
}

// Break Screen Draw logic
void DrawBreakScreen(void) {
    ClearBackground((Color) {56, 133, 138, 0});

    if(!isFinished)
        DrawText(
            value,
            (GetScreenWidth() / 2) - 100,
            100,
            65,
            WHITE
        );
    else
        DrawText(
            msg,
            (GetScreenWidth() - strlen(msg)) / 2 - 100,
            100,
            30,
            RAYWHITE
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
