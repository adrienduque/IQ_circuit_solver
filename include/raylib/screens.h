/**********************************************************************************************
 *
 *   raylib - Advance Game template
 *
 *   Screens Functions Declarations (Init, Update, Draw, Unload)
 *
 *   Copyright (c) 2014-2023 Ramon Santamaria (@raysan5)
 *
 *   This software is provided "as-is", without any express or implied warranty. In no event
 *   will the authors be held liable for any damages arising from the use of this software.
 *
 *   Permission is granted to anyone to use this software for any purpose, including commercial
 *   applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not claim that you
 *     wrote the original software. If you use this software in a product, an acknowledgment
 *     in the product documentation would be appreciated but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not be misrepresented
 *     as being the original software.
 *
 *     3. This notice may not be removed or altered from any source distribution.
 *
 **********************************************************************************************/

/**
 * @note Altered original source file : was a template that I arranged to fit my application
 */

#ifndef SCREENS_H
#define SCREENS_H

#include <raylib/raylib.h>

// #define TILE_VIEWER_MODE

#define DEFAULT_FPS 60

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum GameScreen
{
    LOGO = 0,
    LEVEL_SELECT,
    GAME,
    SOLVER,
} GameScreen;

//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------
extern int level_num_selected;

//----------------------------------------------------------------------------------
// Logo Screen Functions Declaration see screen_logo.c
//----------------------------------------------------------------------------------
void InitLogoScreen(void);
void UpdateLogoScreen(void);
void DrawLogoScreen(void);
void UnloadLogoScreen(void);
int FinishLogoScreen(void);

//----------------------------------------------------------------------------------
// LevelSelect Screen Functions Declaration see screen_level_select.c
//----------------------------------------------------------------------------------
void InitLevelSelectScreen(void);
void UpdateLevelSelectScreen(void);
void DrawLevelSelectScreen(void);
void UnloadLevelSelectScreen(void);
int FinishLevelSelectScreen(void);

//----------------------------------------------------------------------------------
// Game Screen Functions Declaration see screen_game.c
//----------------------------------------------------------------------------------
void InitGameScreen(void);
void UpdateGameScreen(void);
void DrawGameScreen(void);
void UnloadGameScreen(void);
int FinishGameScreen(void);

//----------------------------------------------------------------------------------
// Solver Screen Functions Declaration see screen_solver.c
//----------------------------------------------------------------------------------
void InitSolverScreen(void);
void UpdateSolverScreen(void);
void DrawSolverScreen(void);
void UnloadSolverScreen(void);
int FinishSolverScreen(void);

#endif // SCREENS_H