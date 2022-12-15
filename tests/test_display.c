/**
 * @file test_display.c
 * Unit testing on display.c api
 *
 * @warning This file currently only includes visual testing
 * This is not really a proper "unit testing" file where tests are automated with assertions
 */

#include <local/display.h>
#include <local/piece.h>
#include <minunit.h>
#include <stdio.h>
#include <stdlib.h>

int tests_run = 0;

// function used in all_around_display_test()
static void update_infos(int piece_idx, int side_idx, Vector2_int base_pos, int rotation_state)
{

    static char *name_array[] = {"Line2 1", "Line2 2", "Line3 1", "Line3 2", "Corner 1", "Corner 2", "Square", "L piece", "T piece", "Z piece"};
    system("cls");
    printf("Piece : %s | side %d at (pos : {%d,%d} | rota : %d) \n", name_array[piece_idx], side_idx, base_pos.i, base_pos.j, rotation_state);
}

// helper function for all_around_display_test
bool IfAnyIsPressedKey(int *KeyArray, int nb_of_keys)
{

    static int Key;
    for (int i = 0; i < nb_of_keys; i++)
    {
        Key = KeyArray[i];
        if (IsKeyPressed(Key))
            return true;
    }
    return false;
}

char *all_around_display_test()
{
    /**
     * @bug This is the first time I spotted a memory corruption bug
     * This function show garbage values without segfault
     *
     * Then I tried to do unit testing in test_piece.c, but without success
     */

    /*
    To display the result of the encoding of game pieces on the board
    And to showcase how the visualization of the main algorithm will look like
    Controls :
        - spacebar : change piece displayed
        - F : change side displayed of current piece
        - R : rotate the piece clockwise

        - ZQSD (or WASD) : move the piece accross the board (up,left,down,right respectively)
        Disclaimer : positions where the piece location doesn't make sense are not displayed
        (because I was testing this feature too)

        - C : to toggle drawing of missing connection tiles
        - B : to toggle drawing of border tiles

    See : "showcase assets"/"test_display first example.png" to see what the output looks like

    */
    int control_keys[] = {KEY_W, KEY_A, KEY_S, KEY_D, KEY_R, KEY_F, KEY_SPACE, KEY_C, KEY_B};
    int nb_of_keys = 9;

    setup_display();

    // Initial state displayed
    int piece_idx = 0;
    int side_idx = 0;
    Vector2_int base_pos = {1, 2}; // to start near the middle of the board
    int rotation_state = 0;
    bool show_missing_connection_tiles = true;
    bool show_border_tiles = true;

    // Convenience variables to reverse update when it cannot be drawn
    // only useful in this context and not in the automated backtracking algorithm
    int temp_piece_idx = piece_idx;
    int temp_side_idx = side_idx;
    Vector2_int temp_base_pos = base_pos;
    int temp_rotation_state = rotation_state;

    load_blit_data(piece_idx, side_idx, base_pos, rotation_state);

    bool need_update, first_iteration = true;

    while (!WindowShouldClose())
    {
        need_update = false;

        if (IsKeyPressed(KEY_W))
            increment_pos_in_direction(&temp_base_pos, UP);
        if (IsKeyPressed(KEY_A))
            increment_pos_in_direction(&temp_base_pos, LEFT);
        if (IsKeyPressed(KEY_S))
            increment_pos_in_direction(&temp_base_pos, DOWN);
        if (IsKeyPressed(KEY_D))
            increment_pos_in_direction(&temp_base_pos, RIGHT);

        if (IsKeyPressed(KEY_R))
        {
            temp_rotation_state += 1;
            temp_rotation_state %= NB_OF_DIRECTIONS;
        }

        if (IsKeyPressed(KEY_F))
        {
            temp_side_idx += 1;
            temp_side_idx %= blit_data.piece->nb_of_sides;
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            temp_piece_idx += 1;
            temp_piece_idx %= NB_OF_PIECES;
            temp_side_idx = 0;
        }

        if (IsKeyPressed(KEY_C))
            show_missing_connection_tiles = !show_missing_connection_tiles;

        if (IsKeyPressed(KEY_B))
            show_border_tiles = !show_border_tiles;

        if (IfAnyIsPressedKey(control_keys, nb_of_keys))
            need_update = true;

        // Update cache live data and drawing data only when its necessary
        if (need_update || first_iteration)
        {
            first_iteration = false;

            // Check if the wanted update can be done
            load_blit_data(temp_piece_idx, temp_side_idx, temp_base_pos, temp_rotation_state);
            if (blit_piece_main_data() == PIECE_DOESNT_FIT_INSIDE)
            {
                // we need to revert back changes
                temp_piece_idx = piece_idx;
                temp_side_idx = side_idx;
                temp_base_pos = base_pos;
                temp_rotation_state = rotation_state;
                load_blit_data(piece_idx, side_idx, base_pos, rotation_state);
                blit_piece_main_data();
                // other updates don't have been modified and thus don't need to be reverted
            }
            else
            {

                // we can update everything else

                // first off : tracking update variables
                piece_idx = temp_piece_idx;
                side_idx = temp_side_idx;
                base_pos = temp_base_pos;
                rotation_state = temp_rotation_state;

                // other blit data in piece.c
                blit_outline_tiles();
                if (show_border_tiles)
                    blit_border_tiles();

                // update drawing data cache
                update_all_piece_draw_data(blit_data.piece, show_missing_connection_tiles, show_border_tiles);
            }
            // in all cases update infos
            update_infos(piece_idx, side_idx, base_pos, rotation_state);
        }

        // Always draw cached data
        BeginDrawing();
        ClearBackground(BLACK);
        draw_grid();
        draw_all_piece_data(blit_data.piece, show_missing_connection_tiles, show_border_tiles);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}

char *all_tests()
{
    mu_run_test(all_around_display_test);
    return 0;
}

int main(void)
{
    printf("Press any key to continue testing.\n");
    getchar();
    system("cls");
    char *test_results = all_tests();
    if (test_results != 0)
        printf("Error. Test failed. Msg : %s\n", test_results);
    else
        printf("All tests passed! (%d total tests)\n", tests_run);

    return 0;
}