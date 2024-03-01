#include <string.h>

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static char* title = "POMO";
static char* description = "A pomodoro timer for legends";

//----------------------------------------------------------------------------------
// Logo Screen Functions Definition
//----------------------------------------------------------------------------------

// Logo Screen Initialization logic
void InitLogoScreen(void) {
}

// Logo Screen Update logic
void UpdateLogoScreen(void) {
}

// Logo Screen Draw logic
void DrawLogoScreen(void) {
    DrawText(
        title,
        (GetScreenWidth() / 2) - 100,
        100,
        65,
        RED
    );
    DrawText(
        description,
        (GetScreenWidth() - strlen(description)) / 2 - 200,
        170,
        30,
        RED
    );

    DrawRectangle( 10, 10, 250, 113, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines( 10, 10, 250, 113, BLUE);

    DrawText("Controls:", 20, 20, 10, BLACK);
    DrawText("- Press F for focus time", 40, 40, 10, DARKGRAY);
    DrawText("- Press B for break time", 40, 60, 10, DARKGRAY);
    DrawText("- Press P for pause", 40, 80, 10, DARKGRAY);
    DrawText("- Press R to go home", 40, 100, 10, DARKGRAY);
}

// Logo Screen Unload logic
void UnloadLogoScreen(void)
{
    // Unload LOGO screen variables here!
}

// Logo Screen should finish?
int FinishLogoScreen(void)
{
    return 0;
}
