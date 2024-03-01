#include "raylib.h"
#include "screens.h"

//-----------------------------------------------------------------------------
// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through screens.h
//-----------------------------------------------------------------------------
GameScreen currentScreen = LOGO;

//-----------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//-----------------------------------------------------------------------------
static const int screenWidth = 900;
static const int screenHeight = 500;

//-----------------------------------------------------------------------------
// Local Functions Declaration
//-----------------------------------------------------------------------------
static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
static void UnloadGame(void);
static void UpdateDrawFrame(void);
static void ChangeToScreen(GameScreen screen);

//-----------------------------------------------------------------------------
// Main entry point
//-----------------------------------------------------------------------------
int main(void) {
    InitWindow(screenWidth, screenHeight, "Pomo");
    InitGame();

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        UpdateDrawFrame();
    }

    // Unload current screen data before closing
    switch (currentScreen)
    {
        case LOGO: UnloadLogoScreen(); break;
        // case TITLE: UnloadTitleScreen(); break;
        // case GAMEPLAY: UnloadGameplayScreen(); break;
        // case ENDING: UnloadEndingScreen(); break;
        default: break;
    }

    UnloadGame();
    CloseWindow();

    return 0;
}

// Change to next screen, no transition
static void ChangeToScreen(GameScreen screen) {
    // Unload current screen
    switch (currentScreen) {
        case LOGO: UnloadLogoScreen(); break;
        //case TITLE: UnloadTitleScreen(); break;
        //case GAMEPLAY: UnloadGameplayScreen(); break;
        //case ENDING: UnloadEndingScreen(); break;
        default: break;
    }

    // Init next screen
    switch (screen) {
        case LOGO: InitLogoScreen(); break;
        //case TITLE: InitTitleScreen(); break;
        //case GAMEPLAY: InitGameplayScreen(); break;
        //case ENDING: InitEndingScreen(); break;
        default: break;
    }

    currentScreen = screen;
}

// Initialize game variables
void InitGame(void) {}

// Update game (one frame)
void UpdateGame(void) {
    switch(currentScreen) {
        case LOGO: UpdateLogoScreen(); break;
        default: break;
    }
    ChangeToScreen(currentScreen);
}

// Draw game (one frame)
void DrawGame(void) {
     BeginDrawing();

        ClearBackground(RAYWHITE);

        switch(currentScreen) {
            case LOGO: DrawLogoScreen(); break;
            // case TITLE: DrawTitleScreen(); break;
            // case OPTIONS: DrawOptionsScreen(); break;
            // case GAMEPLAY: DrawGameplayScreen(); break;
            // case ENDING: DrawEndingScreen(); break;
            default: break;
        }

        // DrawFPS(10, 10);

    EndDrawing();
}

// Unload game variables
void UnloadGame(void) {
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
void UpdateDrawFrame(void) {
    UpdateGame();
    DrawGame();
}
