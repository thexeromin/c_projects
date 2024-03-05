#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "library.h"
#include "screens.h"

// Module Variables Definition (local)
static Timer timer = { 0 };
static float maxFocusTime = 5;
static char value[50];
static char* msg = "Time for a break!";

// Focus Screen Initialization logic
void InitFocusScreen(void) {
    StartTimer(&timer, maxFocusTime);
    isFinishedTimer = false;
}

// Focus Screen Update logic
void UpdateFocusScreen(void) {
    if(timer.lifetime <= 0) {
        isFinishedTimer = true;
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

// Focus Screen Draw logic
void DrawFocusScreen(void) {
    ClearBackground((Color) {186, 73, 73, 0});

    if(!isFinishedTimer)
        DrawText(
            value,
            (GetScreenWidth() / 2) - 100,
            100,
            70,
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

// Focus Screen Unload logic
void UnloadFocusScreen(void) {
    // Unload LOGO screen variables here!
    isFinishedTimer = false;
    StopMusicStream(music);
}

// Focus Screen should finish?
int FinishFocusScreen(void) {
    return 0;
}
