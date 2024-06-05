#include <stdio.h>

#include "raylib.h"
#include "library.h"

// Some Defines
#define MAXPIPES    100
#define PIPEHEIGHT  600
#define PIPESPACE   50

// Types and Structures
typedef struct Pipe {
    Rectangle upperPipe;
    Rectangle lowerPipe;
} Pipe;

// Global Variables
static const int screenWidth = 800;
static const int screenHeight = 600;
Pipe pipes[MAXPIPES];
Rectangle bird = {0};
Camera2D camera = { 0 };

// Module Functions
static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
static void UnloadGame(void);
static void UpdateDrawFrame(void);

int main(void) {
    InitWindow(screenWidth, screenHeight, "Flappy Bird");
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
void InitGame(void) {
    int spacing = 0;
    for(int i = 0; i < MAXPIPES; i++) {
        pipes[i].upperPipe.width = 50.0f;
        pipes[i].upperPipe.height = (float)GetRandomValue(50, PIPEHEIGHT - 60);
        pipes[i].upperPipe.x = 200.0f + spacing;
        pipes[i].upperPipe.y = 100.0f;

        pipes[i].lowerPipe.width = 50.0f;
        pipes[i].lowerPipe.height = (float)(
            PIPEHEIGHT - (pipes[i].upperPipe.height + PIPESPACE)
        );
        pipes[i].lowerPipe.x = 200.0f + spacing;
        pipes[i].lowerPipe.y = pipes[i].upperPipe.height + 170.0f;

        spacing += 50.0f + 200.0f;
    }

    bird.width = 25.0f;
    bird.height = 25.0f;
    bird.x = 50.0f;
    bird.y = screenHeight / 2.0f;

    camera.target = (Vector2){ bird.x + 20.0f, bird.y + 20.0f };
    camera.offset = (Vector2){ screenWidth/4.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

// Update game (one frame)
void UpdateGame(void) {
    bird.x += 1;
    bird.y += 1;
    // if (IsKeyDown(KEY_RIGHT)) bird.x += 2;
    if (IsKeyDown(KEY_UP)) bird.y -= 5;
    if (IsKeyDown(KEY_DOWN)) bird.y += 5;
    camera.target = (Vector2){ bird.x + 20, bird.y + 20 };
}

// Draw game (one frame)
void DrawGame(void) {
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);
        for(int i = 0; i < MAXPIPES; i++) {
            DrawRectangleRec(pipes[i].upperPipe, GREEN);
            DrawRectangleRec(pipes[i].lowerPipe, GREEN);
        }
        DrawRectangleRec(bird, RED);
    EndMode2D();

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
