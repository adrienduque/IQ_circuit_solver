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
#include <local/utils.h>            // defines

static void TransitionToScreen(int screen);
static void DrawTransition();
void find_asset_folder_relative_path(void);

static GameScreen currentScreen = LOGO;
static bool onTransition = false;
bool close_window_requested = false;

char assets_folder_relative_path[30];

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

    SetTargetFPS(60);

    InitLogoScreen();
    InitLevelSelectScreen();

    while (!WindowShouldClose() && !close_window_requested)
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
            {
                TransitionToScreen(GAME);
                InitGameScreen();
            }
            break;

        case GAME:
            UpdateGameScreen();
            if (FinishGameScreen() == -1)
                // Go back to previous screen
                TransitionToScreen(LEVEL_SELECT);

            else if (FinishGameScreen() == 1)
            {
                TransitionToScreen(SOLVER);
                InitSolverScreen();
            }
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

        // in order to call the update function before its first corresponding draw call, we need to "waste" 1 transition frame
        if (onTransition)
        {
            BeginDrawing();
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
    }

    UnloadLogoScreen();
    UnloadLevelSelectScreen();
    UnloadGameScreen();
    UnloadSolverScreen();

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
// Helper functions : transition screen
//-------------------------------------------------------------------------

// Request transition to next screen
static void TransitionToScreen(int screen)
{
    onTransition = true;
    currentScreen = screen;
}

static void DrawTransition()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
}

//-------------------------------------------------------------------------
// Helper functions : find assets folder relative path
//-------------------------------------------------------------------------

// As the executables can be run from different common folder locations
// I prefer finding the assets folder dynamically
void find_asset_folder_relative_path(void)
{
    static const char *path_to_test[] = {"assets", "../assets", "../../assets"};
    int idx = -1;
    Image icon;

    do
    {
        idx++;
        icon = LoadImage(TextFormat("%s/icon.png", path_to_test[idx]));

    } while (icon.data == NULL);

    sprintf(assets_folder_relative_path, path_to_test[idx]);
    UnloadImage(icon);
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