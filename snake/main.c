#include "raylib.h"

// Some Defines
#define GRID_SIZE 20

// Types and Structures
typedef struct {
    Rectangle rec;
    Color color;
} Box;

// Global Variables
static const int screenWidth = 500;
static const int screenHeight = 500;
static int GridSideLength = screenWidth / GRID_SIZE;
static Box grid[GRID_SIZE][GRID_SIZE] = {0};
static Vector2 snakePos = {0};
static Vector2 snakeDir = {0};
static const int speed = 10;
static bool isDirX = true;
static Color bg = BLACK;
static Color snakeColor = RED;

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
void InitGame(void) {
    // initial snake pos
    snakePos.x = GRID_SIZE / 2;
    snakePos.y = GRID_SIZE / 2;

    // caluate grid
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            grid[i][j].rec.x = GridSideLength * i;
            grid[i][j].rec.y = GridSideLength * j;
            grid[i][j].rec.width = GridSideLength;
            grid[i][j].rec.height = GridSideLength;

            // initial snake pos
            if(i == (int)snakePos.x && j == (int)snakePos.y)
                grid[i][j].color = snakeColor;
            else
                grid[i][j].color = bg;
        }
    }
}

// Update game (one frame)
void UpdateGame(void) {
    // snake movement
    if(IsKeyPressed(KEY_LEFT)) {
        isDirX = true;
        snakeDir.x = -speed;
    } else if(IsKeyPressed(KEY_RIGHT)) {
        isDirX = true;
        snakeDir.x = speed;
    } else if(IsKeyPressed(KEY_UP)) {
        isDirX = false;
        snakeDir.y = -speed;
    } else if(IsKeyPressed(KEY_DOWN)) {
        isDirX = false;
        snakeDir.y = speed;
    }

    // update snake pos
    if(isDirX)
        snakePos.x += snakeDir.x * GetFrameTime();
    else
        snakePos.y += snakeDir.y * GetFrameTime();

    // threshold check
    if(snakePos.x < 0)
        snakePos.x = GRID_SIZE - 1;
    if(snakePos.x > GRID_SIZE)
        snakePos.x = 0;
    if(snakePos.y < 0)
        snakePos.y = GRID_SIZE - 1;
    if(snakePos.y > GRID_SIZE)
        snakePos.y = 0;

    for(int i = 0; i < GRID_SIZE; i++)
        for(int j = 0; j < GRID_SIZE; j++)
            if(i == (int)snakePos.x && j == (int)snakePos.y)
                grid[i][j].color = snakeColor;
            else
                grid[i][j].color = bg;
}

// Draw game (one frame)
void DrawGame(void) {
    BeginDrawing();
        // draw grid
        for(int i = 0; i < GRID_SIZE; i++)
            for(int j = 0; j < GRID_SIZE; j++)
                DrawRectangleRec(grid[i][j].rec, grid[i][j].color);

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