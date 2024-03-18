#include <stdio.h>

#include "raylib.h"
#include "library.h"

// Some Defines
#define GRID_SIZE 25

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
static Vector2 snakeDir = {0};
static Vector2 foodPos = {0};
static const int speed = 10;
static bool isDirX = true;
static Color bg = BLACK;
static Color snakeColor = RED;
static Color foodColor = YELLOW;
static int score = 0;
char scoreStr[30];
node_t* snake = NULL;

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
    // initial food pos
    foodPos.x = GetRandomValue(0, GRID_SIZE);
    foodPos.y = GetRandomValue(0, GRID_SIZE);
    
    // initial snake pos
    Vector2 initial_pos = { GRID_SIZE / 2, GRID_SIZE / 2 };
    push_start(&snake, initial_pos);

    // initial score
    sprintf(
        scoreStr,
        "Score: %d",
        score
    );

    // caluate grid
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            grid[i][j].rec.x = GridSideLength * i;
            grid[i][j].rec.y = GridSideLength * j;
            grid[i][j].rec.width = GridSideLength;
            grid[i][j].rec.height = GridSideLength;
            grid[i][j].color = bg;
        }
    }
    
    // initial snake pos
    grid[(int)snake->data.x][(int)snake->data.y].color = snakeColor;
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
    if(isDirX) {
        Vector2 new_pos = {
            snake->data.x + snakeDir.x * GetFrameTime(),
            snake->data.y
        };
        push_start(&snake, new_pos);
        remove_last(snake);
    } else {
        Vector2 new_pos = {
            snake->data.x,
            snake->data.y + snakeDir.y * GetFrameTime()
        };
        push_start(&snake, new_pos);
        remove_last(snake);
    }

    // threshold check
    if(snake->data.x < 0)
        snake->data.x = GRID_SIZE - 1;
    if(snake->data.x > GRID_SIZE)
        snake->data.x = 0;
    if(snake->data.y < 0)
        snake->data.y = GRID_SIZE - 1;
    if(snake->data.y > GRID_SIZE)
        snake->data.y = 0;

    // update background
    for(int i = 0; i < GRID_SIZE; i++)
        for(int j = 0; j < GRID_SIZE; j++)
                grid[i][j].color = bg;

    // TODO: iterate over snake & update snake pos color
    node_t* curr_snake = snake;
    while (curr_snake != NULL) {
        grid[(int)curr_snake->data.x][(int)curr_snake->data.y].color = snakeColor;
        curr_snake = curr_snake->next;
    }

    // check for food eat
    if((int)snake->data.x == (int)foodPos.x && (int)snake->data.y == (int)foodPos.y) {
        foodPos.x = GetRandomValue(0, GRID_SIZE - 1);
        foodPos.y = GetRandomValue(0, GRID_SIZE - 1);

        score += 5;
        sprintf(
            scoreStr,
            "Score: %d",
            score
        );

        // increase snake length
        Vector2 pos = { snake->data.x - 1, snake->data.y - 1 };
        push_end(snake, pos);
    }
    
    // update food
    grid[(int)foodPos.x][(int)foodPos.y].color = foodColor;
}

// Draw game (one frame)
void DrawGame(void) {
    BeginDrawing();
        // draw grid
        for(int i = 0; i < GRID_SIZE; i++)
            for(int j = 0; j < GRID_SIZE; j++)
                DrawRectangleRec(grid[i][j].rec, grid[i][j].color);

        // draw score
        DrawText(scoreStr, screenWidth - 120, 10, 20, WHITE);
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
