/**
 * @file test_piece.c
 * Unit testing on piece.c api
 *
 *
 */

#include <local/piece.h>
#include <minunit.h>
#include <stdio.h>
#include <stdlib.h>

int tests_run = 0;

char *test_load_blit_data()
{
    // maybe multiple load_blit_data breaks it ?

    /**
     * @bug This function is completely broken and I don't know why and don't know how to debug it
     * It's about memory corruption stuff, but I don't get any segfault, only garbage values
     * I even have had undefined behavior where a function had been called twice or none at all, like doubling printf ?
     * I can't debug it, I will try to simplify the code instead
     */

    // ------ 1

    int piece_idx = 0;
    int side_idx = 1;
    Vector2_int base_pos = {1, 2};
    int rotation_state = 3;

    load_blit_data(piece_idx, side_idx, base_pos, rotation_state);

    printf("blit_data.piece = %p\n&(piece_array[piece_idx]) = %p\n\n", blit_data.piece, &(piece_array[piece_idx]));
    mu_assert("Bug spotted", (blit_data.piece == &(piece_array[piece_idx])));

    printf("blit_data.side = %p\n&(piece_array[piece_idx].side_array[side_idx]) = %p\n\n", blit_data.side, &(piece_array[piece_idx].side_array[side_idx]));
    mu_assert("Bug spotted", (blit_data.side == &(piece_array[piece_idx].side_array[side_idx])));

    printf("blit_data.piece->current_side_idx = %d\npiece_array[piece_idx].current_side_idx = %d\n\n", blit_data.piece->current_side_idx, piece_array[piece_idx].current_side_idx);
    mu_assert("bug spotted", (blit_data.piece->current_side_idx == piece_array[piece_idx].current_side_idx));

    // ------ 2

    piece_idx = 1;
    side_idx = 2;
    base_pos.i = 2;
    base_pos.j = 3;
    rotation_state = 2;

    load_blit_data(piece_idx, side_idx, base_pos, rotation_state);

    printf("blit_data.piece = %p\n&(piece_array[piece_idx]) = %p\n\n", blit_data.piece, &(piece_array[piece_idx]));
    mu_assert("Bug spotted", (blit_data.piece == &(piece_array[piece_idx])));

    printf("blit_data.side = %p\n&(piece_array[piece_idx].side_array[side_idx]) = %p\n\n", blit_data.side, &(piece_array[piece_idx].side_array[side_idx]));
    mu_assert("Bug spotted", (blit_data.side == &(piece_array[piece_idx].side_array[side_idx])));

    printf("blit_data.piece->current_side_idx = %d\npiece_array[piece_idx].current_side_idx = %d\n\n", blit_data.piece->current_side_idx, piece_array[piece_idx].current_side_idx);
    mu_assert("bug spotted", (blit_data.piece->current_side_idx == piece_array[piece_idx].current_side_idx));

    return 0;
}

char *test_blit_piece_main_data()
{

    printf("------------ Normal case 1 --------------\n");
    int piece_idx = 0;
    int side_idx = 1;
    Vector2_int base_pos = {1, 2};
    int rotation_state = 0;

    load_blit_data(piece_idx, side_idx, base_pos, rotation_state);

    Piece *piece = &(piece_array[piece_idx]);
    Side *side = &(piece->side_array[side_idx]);
    Tile *tile;

    blit_piece_main_data();

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
    mu_assert("Bug spotted", ((tile->nb_of_connections == 1) && (tile->connection_direction_array[0] == DOWN) && (tile->connection_direction_array[1] == LEFT)));

    /**
     * @bug This test function isn't even finished
     */

    return 0;
}

char *all_tests()
{
    mu_run_test(test_load_blit_data);
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