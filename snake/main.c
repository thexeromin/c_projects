#include "raylib.h"

// Some Defines

// Types and Structures

// Global Variables
static const int screenWidth = 500;
static const int screenHeight = 500;

// Module Functions
static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
static void UnloadGame(void);
static void UpdateDrawFrame(void);

int main(void) {
    InitWindow(screenWidth, screenHeight, "Snake Game");
    InitGame();

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        UpdateDrawFrame();
    }

    UnloadGame();
    CloseWindow();

    return 0;
}

// Initialize game variables
void InitGame(void) {}

// Update game (one frame)
void UpdateGame(void) {}

// Draw game (one frame)
void DrawGame(void) {
    BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Hello, World", 190, 200, 20, LIGHTGRAY);
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