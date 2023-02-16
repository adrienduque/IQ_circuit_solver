/**
 * @file main.c
 *
 * Contains the main function, starting point of the whole program
 *
 * main.c has mainly become a screen manager, see raylig game template and examples
 */

#include <stdio.h>
#include <stdlib.h> // system

#include <raylib/raylib.h>  // general helper functions of raylib
#include <raylib/screens.h> // custom main helper functions see a raylib game template

#include <local/search_algorithm.h> // run_algorithm_*** functions
#include <local/display.h>          // setup_display
#include <local/utils.h>            // find_asset_folder_relative_path and defines

static void InitStaticScreens(void);
static void UnloadStaticScreens(void);

static void UnloadCurrentDynamicScreen(void);
static void InitCurrentDynamicScreen(void);

static void TransitionToScreen(int screen);
static void DrawTransition();

static GameScreen currentScreen;
static bool onTransition;

/**
 * @todo : https://github.com/raysan5/raylib/discussions/1326
 * + record a video of solver when I decided to not upgrade the solver anymore
 * + https://ezgif.com/video-to-gif to show to github
 */

int main(void)
{
#ifndef AUTOMATED_RUNS

    setup_display((BOARD_WIDTH + 9) * tile_px_width, (BOARD_HEIGHT + 5) * tile_px_width);
    SetWindowTitle("Spaghetti Solver");

    find_asset_folder_relative_path();

    Image icon = LoadImage(TextFormat("%s/icon.png", assets_folder_relative_path));
    ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    SetWindowIcon(icon);
    UnloadImage(icon);

    SetTargetFPS(DEFAULT_FPS);

    InitStaticScreens();

    currentScreen = LOGO;
    onTransition = false;

    while (!WindowShouldClose())
    {
        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------

        switch (currentScreen)
        {
        case LOGO:
            UpdateLogoScreen();
            if (FinishLogoScreen())
                TransitionToScreen(LEVEL_SELECT);
            break;

        case LEVEL_SELECT:
            UpdateLevelSelectScreen();
            if (FinishLevelSelectScreen())
                TransitionToScreen(GAME);
            break;

        case GAME:
            UpdateGameScreen();
            if (FinishGameScreen() == -1)
                // Go back to previous screen
                TransitionToScreen(LEVEL_SELECT);

            else if (FinishGameScreen() == 1)
                TransitionToScreen(SOLVER);

            break;

        case SOLVER:
            UpdateSolverScreen();
            if (FinishSolverScreen())
                TransitionToScreen(LEVEL_SELECT);

            break;

        default:
            break;
        }

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        // in order to call the update function before its first corresponding draw call, we need to "waste" 1 transition frame
        if (onTransition)
        {
            DrawTransition();
            onTransition = false;
            EndDrawing();
            continue;
        }

        switch (currentScreen)
        {
        case LOGO:
            DrawLogoScreen();
            break;
        case LEVEL_SELECT:
            DrawLevelSelectScreen();
            break;
        case GAME:
            DrawGameScreen();
            break;
        case SOLVER:
            DrawSolverScreen();
            break;
        default:
            break;
        }
        EndDrawing();
    }

    UnloadStaticScreens();
    UnloadCurrentDynamicScreen(); // (works only if we exit fram GAME or SOLVER screen)

    CloseWindow();

#else

    for (int level_num = 49; level_num <= 120; level_num++)
        run_algorithm_without_display(level_num);

    printf("\n\nPart with display\n\n");

    for (int level_num = 49; level_num <= 120; level_num++)
        run_algorithm_with_display(level_num, 0);

#endif

    return 0;
}

//-------------------------------------------------------------------------
// Helper functions : Init / unload functions (mostly for code clarity)
//-------------------------------------------------------------------------

static void InitStaticScreens(void)
{

    InitLogoScreen();
    InitLevelSelectScreen();
}

static void UnloadStaticScreens(void)
{

    UnloadLogoScreen();
    UnloadLevelSelectScreen();
}

static void UnloadCurrentDynamicScreen(void)
{
    // I only include screens that have their Init functions called multiple times through program execution
    switch (currentScreen)
    {
    case GAME:
        UnloadGameScreen();
        break;
    case SOLVER:
        UnloadSolverScreen();
        break;

    default:
        break;
    }
}

static void InitCurrentDynamicScreen(void)
{
    // I only include screens that have their Init functions called multiple times through program execution
    switch (currentScreen)
    {
    case GAME:
        InitGameScreen();
        break;
    case SOLVER:
        InitSolverScreen();
        break;

    default:
        break;
    }
}
//-------------------------------------------------------------------------
// Helper functions : transition screen
//-------------------------------------------------------------------------

// Request transition to next screen
static void TransitionToScreen(int screen)
{
    UnloadCurrentDynamicScreen();
    onTransition = true;
    currentScreen = screen;
    InitCurrentDynamicScreen();
}

static void DrawTransition()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

void previous_main(void)
{

    int level_num;

    printf("Welcome to Spaghetti solver.\n\n");
    printf("Enter the level number you want to solve (49 to 120 included) : ");
    scanf("%3d", &level_num);
    while (level_num < 49 || level_num > 120)
    {
        system("cls");
        printf("Enter the level number you want to solve (49 to 120 included) : ");
        scanf("%3d", &level_num);
    }

    //    I feel like 10 fps is a good delay between each frame to see what's the algorithm doing
    // run_algorithm_with_display(level_num, 10);
    // run_algorithm_without_display(level_num);

    run_algorithm_with_extra_display(level_num, 0);

    printf("\n");
}