/**
 * @file test_piece.c
 * Unit testing on piece.c api
 *
 *
 */

#include <local/utils.h> // Vector2_int, helper functions and defines

#include <local/piece.h>
#include <minunit.h>
#include <stdio.h>  // printf, getchar
#include <stdlib.h> // system

int tests_run = 0;

char *test_blit_piece_main_data()
{

    Piece piece_array[NB_OF_PIECES];
    load_piece_array(piece_array);

    printf("------------ Normal case 1 --------------\n");
    int piece_idx = 0;
    int side_idx = 0;
    Vector2_int base_pos = {1, 2};
    int rotation_state = 0;

    Piece *piece = piece_array + piece_idx;
    Side *side = (piece->side_array) + side_idx;

    blit_piece_main_data(piece, side_idx, base_pos, rotation_state);

    Tile *tile;

    tile = &(side->tile_array[0]);
    printf("Normal tile 0 should be at {1,2} after blit\n");
    printf("absolute pos : {%d,%d}\n\n", tile->absolute_pos.i, tile->absolute_pos.j);
    mu_assert("Bug spotted", are_pos_equal(&(tile->absolute_pos), &((Vector2_int){1, 2})));

    tile = &(side->tile_array[1]);
    printf("Normal tile 1 should be at {2,2} after blit\n");
    printf("absolute pos : {%d,%d}\n\n", tile->absolute_pos.i, tile->absolute_pos.j);
    mu_assert("Bug spotted", are_pos_equal(&(tile->absolute_pos), &((Vector2_int){2, 2})));

    printf("Legend : RIGHT is 0 | DOWN is 1 | LEFT is 2 | UP is 3\n\n");

    tile = &(side->tile_array[0]);
    printf("Normal tile 0 should have 1 connection to the RIGHT\n");
    printf("nb_of_connections : %d | connection_direction 0 : %d\n\n", tile->nb_of_connections, tile->connection_direction_array[0]);
    mu_assert("Bug spotted", ((tile->nb_of_connections == 1) && (tile->connection_direction_array[0] == RIGHT)));

    tile = &(side->tile_array[1]);
    printf("Normal tile 1 should have 2 connections (DOWN and LEFT)\n");
    printf("nb_of_connections : %d | connection_direction 0 : %d | connection_direction 1 : %d\n\n", tile->nb_of_connections, tile->connection_direction_array[0], tile->connection_direction_array[1]);
    mu_assert("Bug spotted", ((tile->nb_of_connections == 2) && (tile->connection_direction_array[0] == DOWN) && (tile->connection_direction_array[1] == LEFT)));

    /**
     * @warning this test function and this file are not finished yet, but it seems that everything is correct with the visual test of test_display.c
     * Thus writing this test function is not my priority
     *
     * This principle was applied a lot more than I expected through the whole project
     */

    return 0;
}

char *all_tests()
{
    mu_run_test(test_blit_piece_main_data);
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
    {
        printf("All tests passed! (%d total tests)\n", tests_run);
    }

    return 0;
}