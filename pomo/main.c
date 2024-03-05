#include <stdio.h>

#include "raylib.h"
#include "screens.h"

// Shared Variables Definition (global)
bool isFinishedTimer;
Music music;
GameScreen currentScreen = LOGO;

// Local Variables Definition (local to this module)
static const int screenWidth = 900;
static const int screenHeight = 500;
static bool musicPlayed = false;

// Local Functions Declaration
static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
static void UnloadGame(void);
static void UpdateDrawFrame(void);
static void ChangeToScreen(GameScreen screen);

int main(void) {
    InitWindow(screenWidth, screenHeight, "Pomodoro");
    InitAudioDevice();
    InitGame();

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        UpdateDrawFrame();
    }

    // Unload current screen data before closing
    switch (currentScreen) {
        case LOGO: UnloadLogoScreen(); break;
        case FOCUS: UnloadFocusScreen(); break;
        case BREAK: UnloadBreakScreen(); break;
        default: break;
    }

    UnloadGame();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

// Change to next screen, no transition
static void ChangeToScreen(GameScreen screen) {
    // Unload current screen
    switch (currentScreen) {
        case LOGO: UnloadLogoScreen(); break;
        case FOCUS: UnloadFocusScreen(); break;
        case BREAK: UnloadBreakScreen(); break;
        default: break;
    }

    // Init next screen
    switch (screen) {
        case LOGO: InitLogoScreen(); break;
        case FOCUS: InitFocusScreen(); break;
        case BREAK: InitBreakScreen(); break;
        default: break;
    }

    currentScreen = screen;
}

// Initialize game variables
void InitGame(void) {
    music = LoadMusicStream("resources/kichen-timer.mp3");
    music.looping = false;
    musicPlayed = false;
}

// Update game (one frame)
void UpdateGame(void) {
    UpdateMusicStream(music);
    switch(currentScreen) {
        case LOGO: UpdateLogoScreen(); break;
        case FOCUS: UpdateFocusScreen(); break;
        case BREAK: UpdateBreakScreen(); break;
        default: break;
    }

    if(IsKeyPressed(KEY_F))
        ChangeToScreen(FOCUS);
    if(IsKeyPressed(KEY_R))
        ChangeToScreen(LOGO);
    if(IsKeyPressed(KEY_B))
        ChangeToScreen(BREAK);

    if(isFinishedTimer) {
        PlayMusicStream(music);
    }
}

// Draw game (one frame)
void DrawGame(void) {
     BeginDrawing();

        switch(currentScreen) {
            case LOGO: DrawLogoScreen(); break;
            case FOCUS: DrawFocusScreen(); break;
            case BREAK: DrawBreakScreen(); break;
            default: break;
        }

        // DrawFPS(10, 10);

    EndDrawing();
}

// Unload game variables
void UnloadGame(void) {
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
    UnloadMusicStream(music);
}

// Update and Draw (one frame)
void UpdateDrawFrame(void) {
    UpdateGame();
    DrawGame();
}
