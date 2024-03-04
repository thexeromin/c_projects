#ifndef SCREENS_H
#define SCREENS_H

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum GameScreen {
    UNKNOWN = -1,
    LOGO = 0,
    FOCUS,
    BREAK,
} GameScreen;

//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------
extern GameScreen currentScreen;
// extern Font font;
// extern Music music;
// extern Sound fxCoin;

//----------------------------------------------------------------------------------
// Logo Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitLogoScreen(void);
void UpdateLogoScreen(void);
void DrawLogoScreen(void);
void UnloadLogoScreen(void);
int FinishLogoScreen(void);

//----------------------------------------------------------------------------------
// Focus Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitFocusScreen(void);
void UpdateFocusScreen(void);
void DrawFocusScreen(void);
void UnloadFocusScreen(void);
int FinishFocusScreen(void);

//----------------------------------------------------------------------------------
// Break Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitBreakScreen(void);
void UpdateBreakScreen(void);
void DrawBreakScreen(void);
void UnloadBreakScreen(void);
int FinishBreakScreen(void);

#endif // SCREENS_H
