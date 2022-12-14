/**
 * @file test_utils.c
 * Unit testing on utils.c api
 */

#include <local/utils.h>
#include <minunit.h>
#include <stdio.h>
#include <stdlib.h>

int tests_run = 0;

char *test_rotate_pos()
{
    RelativePos test_input = {1, 2};
    RelativePos rotate_output;

    rotate_output = rotate_pos(test_input, RIGHT);
    printf("right rotation of {1,2} return {%d,%d}\n", rotate_output.i, rotate_output.j);
    mu_assert("right rotation of {1,2}, should return {1,2}", ((rotate_output.i == 1) && (rotate_output.j == 2)));

    rotate_output = rotate_pos(test_input, DOWN);
    printf("down rotation of {1,2} return {%d,%d}\n", rotate_output.i, rotate_output.j);
    mu_assert("down rotation of {1,2}, should return {-2,1}", ((rotate_output.i == -2) && (rotate_output.j == 1)));

    rotate_output = rotate_pos(test_input, LEFT);
    printf("left rotation of {1,2} return {%d,%d}\n", rotate_output.i, rotate_output.j);
    mu_assert("left rotation of {1,2}, should return {-1,-2}", ((rotate_output.i == -1) && (rotate_output.j == -2)));

    rotate_output = rotate_pos(test_input, UP);
    printf("up rotation of {1,2} return {%d,%d}\n", rotate_output.i, rotate_output.j);
    mu_assert("up rotation of {1,2}, should return {2,-1}", ((rotate_output.i == 2) && (rotate_output.j == -1)));
    return 0;
}

char *test_pos_traductions()
{
    printf("Double traduction should return the exact same input, no matter the order of operations.\n");
    printf("As long as input is a valid position (inside board), else error code is return after the first operation.\n");
    printf("(flat_pos)(-1) means invalid flat position (out of bounds)\n");
    // temp variables used in loops
    RelativePos test_rel_pos;
    int test_flat_pos;

    // ----------------------------------- Test rel -> flat ----------------------------

    int nb_of_rel_pos_to_test = 6;
    RelativePos rel_pos_array[] = {
        {1, 2},
        {-1, 2},
        {-1, -2},
        {1, -2},
        {BOARD_WIDTH, 0},
        {0, BOARD_HEIGHT},
    };
    int expected_flat_pos_output_array[] = {17, INVALID_FLAT_POS, INVALID_FLAT_POS, INVALID_FLAT_POS, INVALID_FLAT_POS, INVALID_FLAT_POS, INVALID_FLAT_POS};

    for (int i = 0; i < nb_of_rel_pos_to_test; i++)
    {
        test_rel_pos = rel_pos_array[i];
        test_flat_pos = relative_pos_to_flat_pos(test_rel_pos);
        printf("{%d,%d} (to flat)-> %d\n", test_rel_pos.i, test_rel_pos.j, test_flat_pos);
        mu_assert("Error see above", test_flat_pos == expected_flat_pos_output_array[i]);
        printf("\n");
    }
    // ----------------------------------- Test flat -> rel ----------------------------

    /**
     * @warning As flat_pos_to_relative_pos function is only with controlled input for now
     * the function assumes that its input is valid to skip useless comparaisons

     * */
    // int nb_of_flat_pos_to_test = 3;
    // int flat_pos_array[] = {17, -3, BOARD_TOTAL_NB_TILES};

    // RelativePos expected_rel_pos_output_array[] = {{1, 2}, INVALID_REL_POS, INVALID_REL_POS};

    // for (int idx = 0; idx < nb_of_flat_pos_to_test; idx++)
    // {
    //     test_flat_pos = flat_pos_array[idx];
    //     test_rel_pos = flat_pos_to_relative_pos(test_flat_pos);
    //     printf("%d (to rel) -> {%d,%d}\n", test_flat_pos, test_rel_pos.i, test_rel_pos.j);
    //     mu_assert("Error see above", ((test_rel_pos.i == expected_rel_pos_output_array[idx].j) && (test_rel_pos.j == expected_rel_pos_output_array[idx].j)));
    //     printf("\n");
    // }

    // ----------------------------------- Test flat -> rel -> flat -------------------
    test_flat_pos = 17;
    mu_assert("double traduction from (flat_pos)17 should return 17", test_flat_pos == relative_pos_to_flat_pos(flat_pos_to_relative_pos(test_flat_pos)));

    // ----------------------------------- Test rel -> flat -> rel -------------------
    test_rel_pos.i = 1;
    test_rel_pos.j = 2;
    RelativePos result_test_rel_pos = flat_pos_to_relative_pos(relative_pos_to_flat_pos(test_rel_pos));
    mu_assert("double traduction from (rel_pos){1,2} should return {1,2}", ((result_test_rel_pos.i == test_rel_pos.i) && (result_test_rel_pos.j == test_rel_pos.j)));

    return 0;
}

char *test_direction_functions()
{
    Direction reverse_expected_output_array[] = {LEFT, UP, RIGHT, DOWN};
    Direction output_direction;
    printf("RIGHT : 0 | DOWN : 1 | LEFT : 2 | UP : 3\n");
    for (int i = RIGHT; i < NB_OF_DIRECTIONS; i++)
    {
        output_direction = reverse_direction(i);
        printf("reverse(%d) -> %d\n", i, output_direction);
        mu_assert("reverse function not correct", (output_direction == reverse_expected_output_array[i]));
    }

    return 0;
}

char *all_tests()
{
    mu_run_test(test_rotate_pos);
    mu_run_test(test_pos_traductions);
    mu_run_test(test_direction_functions);
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