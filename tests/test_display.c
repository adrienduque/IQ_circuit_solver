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
static void update_infos(int piece_idx, int side_idx, int flat_base_position, int rotation_state)
{

    static char *name_array[] = {"Line2 1", "Line2 2", "Line3 2", "Corner 1", "Corner 2", "Square", "L piece", "T piece", "Z piece"};
    system("cls");
    printf("Piece : %s | side %d at (pos : %d | rota : %d) \n", name_array[piece_idx], side_idx, flat_base_position, rotation_state);
}

char *all_around_display_test()
{
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

    See : "showcase assets"/"test_display first example.png" to see what the output looks like

    */

    setup_display();

    // Initial state displayed
    int flat_base_position = 17; // corresponds to {1,2} (to initialize the blit in the middle of the grid)
    int rotation_state = 0;
    int piece_idx = 0;
    int side_idx = 0;

    // Live data holders
    Side_compute_only side_data;
    int border_tiles[MAX_NB_OF_BORDER_TILE_PER_SIDE];
    RelativePos outline_edge_points[MAX_NB_OF_EDGE_POINTS];

    // Convenience variables, only useful to avoid glitched display (or rather impression of non responsivness)
    int previous_flat_base_position = flat_base_position;
    int previous_rotation_state = rotation_state;
    int previous_piece_idx = piece_idx;
    int previous_side_idx = side_idx;

    // Loading static piece data of initial state
    Piece current_piece = piece_array[piece_idx];
    Side current_side = current_piece.side_array[side_idx];

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_W))
            flat_base_position += flat_pos_direction_increment[UP];
        if (IsKeyPressed(KEY_A))
            flat_base_position += flat_pos_direction_increment[LEFT];
        if (IsKeyPressed(KEY_S))
            flat_base_position += flat_pos_direction_increment[DOWN];
        if (IsKeyPressed(KEY_D))
            flat_base_position += flat_pos_direction_increment[RIGHT];

        if (IsKeyPressed(KEY_R))
        {
            rotation_state += 1;
            rotation_state %= NB_OF_DIRECTIONS;
        }

        if (IsKeyPressed(KEY_F))
        {
            side_idx += 1;
            side_idx %= current_piece.nb_of_sides;
            current_side = current_piece.side_array[side_idx];
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            piece_idx += 1;
            piece_idx %= NB_OF_PIECES;
            current_piece = piece_array[piece_idx];
            side_idx = 0;
            current_side = current_piece.side_array[side_idx];
        }

        // Update by loading live data in live data holders

        BeginDrawing(); // it is obligatory to call this function first to have a responsive window

        if (blit_side_data(&side_data, current_side, flat_base_position, rotation_state) == SIDE_DOESNT_FIT_INSIDE)
        { // out of bounds case, do not draw and revert changes
            piece_idx = previous_piece_idx;
            side_idx = previous_side_idx;
            flat_base_position = previous_flat_base_position;
            rotation_state = previous_rotation_state;
            current_piece = piece_array[piece_idx];
            current_side = current_piece.side_array[side_idx];

            EndDrawing();
        }
        else
        {
            // case where the piece can be displayed -> update other live data
            blit_border_tiles_of_side(border_tiles, current_side, flat_base_position, rotation_state);
            blit_outline_edges_points_of_side(outline_edge_points, current_side, flat_base_position, rotation_state);

            previous_piece_idx = piece_idx;
            previous_side_idx = side_idx;
            previous_flat_base_position = flat_base_position;
            previous_rotation_state = rotation_state;

            update_infos(piece_idx, side_idx, flat_base_position, rotation_state);

            // Display
            ClearBackground(BLACK);
            draw_grid();
            for (int i = 0; i < side_data.nb_of_tiles; i++)
                draw_tile(side_data.tile_array[i]);
            for (int i = 0; i < side_data.nb_of_missing_connection_tiles; i++)
                draw_missing_connection_tile(side_data.missing_connection_tile_array[i]);
            for (int i = 0; i < current_side.nb_of_border_tiles; i++)
                draw_border_tile(border_tiles[i]);
            draw_outline_edge_points(outline_edge_points, current_side.nb_of_edge_points);
            EndDrawing();
        }
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