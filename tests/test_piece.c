/**
 * @file test_piece.c
 * Unit testing on piece.c api
 *
 * @warning See test_display.c where blit_side_data, blit_border_tiles_of_side, blit_outline_edges_points_of_side functions are used in the intended way
 * Writing unit test for these functions is not my priority if everything seems to work, at least visually
 * I might come back to this file if I spot bugs in the future main algorithm
 *
 */

#include <local/piece.h>
#include <minunit.h>
#include <stdio.h>
#include <stdlib.h>

int tests_run = 0;

// char *test_blit_side_data()
// {

//     Piece test_piece = piece_array[LINE2_1];
//     Side test_side = test_piece.side_array[0];

//     int flat_base_position = 10;
//     int rotation_state = 1;

//     Side_compute_only expected_output = {
//         .nb_of_tiles = 2,
//         .nb_of_missing_connection_tiles = 1,
//         .tile_array = {
//             {.tile_type = point, .relative_pos = {0, 0}, .flat_position = 10, .nb_of_connections = 1, .connection_direction_array = {DOWN}},
//             {.tile_type = bend, .relative_pos = {1, 0}, .flat_position = 18, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}},
//         },
//         .missing_connection_tile_array = {
//             {.tile_type = missing_connection, .relative_pos = {1, 1}, .flat_position = 17, .nb_of_connections = 1, .connection_direction_array = {LEFT}},
//         },
//     };

//     Side_compute_only output;
//     blit_side_data(&output, test_side, flat_base_position, rotation_state);
//     // mu_assert("normal case of place_side is not correct", ());
//     // must write an is_equal function for Side_compute_only structure to do that
//     return 0;
// }

char *all_tests()
{
    // mu_run_test(test_blit_side_data);
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