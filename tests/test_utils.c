/**
 * @file test_utils.c
 * Unit testing on utils.c api
 */

#include <local/utils.h>
#include <minunit.h>
#include <stdio.h>  // printf, getchar
#include <stdlib.h> // system

int tests_run = 0;

bool close_window_requested;

char *test_rotate_pos()
{
    Vector2_int test_input = {1, 2};
    Vector2_int rotate_output;

    rotate_output = test_input;
    rotate_pos(&rotate_output, RIGHT);
    printf("right rotation of {1,2} return {%d,%d}\n", rotate_output.i, rotate_output.j);
    mu_assert("right rotation of {1,2}, should return {1,2}", ((rotate_output.i == 1) && (rotate_output.j == 2)));

    rotate_output = test_input;
    rotate_pos(&rotate_output, DOWN);
    printf("down rotation of {1,2} return {%d,%d}\n", rotate_output.i, rotate_output.j);
    mu_assert("down rotation of {1,2}, should return {-2,1}", ((rotate_output.i == -2) && (rotate_output.j == 1)));

    rotate_output = test_input;
    rotate_pos(&rotate_output, LEFT);
    printf("left rotation of {1,2} return {%d,%d}\n", rotate_output.i, rotate_output.j);
    mu_assert("left rotation of {1,2}, should return {-1,-2}", ((rotate_output.i == -1) && (rotate_output.j == -2)));

    rotate_output = test_input;
    rotate_pos(&rotate_output, UP);
    printf("up rotation of {1,2} return {%d,%d}\n", rotate_output.i, rotate_output.j);
    mu_assert("up rotation of {1,2}, should return {2,-1}", ((rotate_output.i == 2) && (rotate_output.j == -1)));

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