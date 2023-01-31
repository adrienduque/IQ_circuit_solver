/**
 * @file utils.c
 *
 * Includes all little math-like functions and macros related to positionning on the board
 * A position on the board is represented by 2 ints :
 *      -by using "Vector2_int" struct -> (i,j) (2D : horizontal / vertical int index of a tile)
 *      works like pixel position on a screen (j increments downwards, (0,0) is in top left corner), ...)
 *
 *
 * Also includes helper functions for Direction type (which are encoded as int, and mainly used to specify direction of tile connections)
 */

#include <stdbool.h>
#include <stdlib.h> // abs

#include <local/utils.h>

// ---------------------------------------- Direction functions -------------------------------------------

// Function to reverse input direction
// e.g. : reverse_direction(RIGHT) -> LEFT
Direction reverse_direction(Direction direction)
{
    // directions are underlying ints, see defintion of RIGHT, DOWN, ... macros in utils.h
    return (direction + 2) % NB_OF_DIRECTIONS;
}

// Function to rotate clockwise the input direction
// e.g. : rotate_direction(RIGHT,1) -> DOWN
// e.g. : rotate_direction(DOWN,2) == reverse_direction(DOWN) -> UP
Direction rotate_direction(Direction direction, int nb_of_clockwise_90_degres_rotation)
{
    // directions are underlying ints, see defintion of RIGHT, DOWN, ... macros in utils.h
    return (direction + nb_of_clockwise_90_degres_rotation) % NB_OF_DIRECTIONS;
}

// -------------------------------------- 2D transformation functions ------------------------------------

/**
 * identity matrix
 */
// static RotationMatrix right_rotation_mat = {1, 0, 0, 1};

/**
 * rotation from right direction (base direction) to down
 * it is a 90° rotation :
 * i unitary vector becomes j  |[1,0]  -> [0,1]
 * j unitary vector becomes -i |[0,1] -> [-1,0]
 * we can see transpose matrix above      ^^
 */
// static RotationMatrix down_rotation_mat = {0, -1, 1, 0};

/**
 * rotation from right direction (base direction) to left
 * it is a 180° rotation :
 * i unitary vector becomes -i |[1,0]  -> [-1,0]
 * j unitary vector becomes -j |[0,1] -> [0,-1]
 * we can see transpose matrix above      ^^
 */
// static RotationMatrix left_rotation_mat = {-1, 0, 0, -1};

/**
 * rotation from right direction (base direction) to up
 * it is a 270° rotation :
 * i unitary vector becomes -j |[1,0]  -> [0,-1]
 * j unitary vector becomes i  |[0,1] ->  [1,0]
 * we can see transpose matrix above      ^^
 */
// static RotationMatrix up_rotation_mat = {0, 1, -1, 0};

// Array of matrices used for rotation from RIGHT (assumed based direction of all relative positionning data) to another direction
// See rotate_pos function
// (Explanation of why the raw data is what it is, in the comments above)
static RotationMatrix rotation_mat_array[] = {
    [RIGHT] = {1, 0, 0, 1},
    [DOWN] = {0, -1, 1, 0},
    [LEFT] = {-1, 0, 0, -1},
    [UP] = {0, 1, -1, 0},
};

void matrix_mul(Vector2_int *pos, const RotationMatrix *matrix)
{
    static int temp_new_i, temp_new_j;
    temp_new_i = pos->i * matrix->m0 + pos->j * matrix->m1;
    temp_new_j = pos->i * matrix->m2 + pos->j * matrix->m3;

    pos->i = temp_new_i;
    pos->j = temp_new_j;
}

void rotate_pos(Vector2_int *pos, int rotation_state)
{
    matrix_mul(pos, &(rotation_mat_array[rotation_state]));
}

void translate_pos(Vector2_int *pos, const Vector2_int *translate_vector)
{
    pos->i = pos->i + translate_vector->i;
    pos->j = pos->j + translate_vector->j;
}

static Vector2_int pos_directionnal_increment[] = {
    [RIGHT] = {1, 0},
    [DOWN] = {0, 1},
    [LEFT] = {-1, 0},
    [UP] = {0, -1},
};

void increment_pos_in_direction(Vector2_int *pos, Direction direction)
{
    translate_pos(pos, &(pos_directionnal_increment[direction]));
}

bool is_pos_inside_board(const Vector2_int *pos)
{
    return ((pos->i >= 0) && (pos->i < BOARD_WIDTH) && (pos->j >= 0) && (pos->j < BOARD_HEIGHT));
}

bool are_pos_equal(const Vector2_int *pos1, const Vector2_int *pos2)
{
    return ((pos1->i == pos2->i) && (pos1->j == pos2->j));
}

static Vector2_int invalid_pos = {-1, -1};

void set_invalid_pos(Vector2_int *pos)
{
    pos->i = invalid_pos.i;
    pos->j = invalid_pos.j;
}

bool is_pos_valid(const Vector2_int *pos)
{
    return !are_pos_equal(pos, &invalid_pos);
}

int manhattan_dist(const Vector2_int *pos1, const Vector2_int *pos2)
{
    return abs((pos1->i) - (pos2->i)) + abs((pos1->j) - (pos2->j));
}

// -------------------------------------- Math needed for main search algorithm ------------------------------------

// function to generate all r-combinations of input array (which is necessary an array of ints here)
// (max r = 10 in this implementation)
// the result is stored in next_combination_placeholder by reference
// the function needs to be called repeatedly for all combinations to be yield
// function derived from : https://scvalex.net/posts/cp5/
int generate_next_combination(const int *input_int_array, int input_array_length, int *next_combination_placeholder, int r)
{
    if (r == 0)
        return 0;

    static int i;
    static int n;
    static int comb[10];
    static bool is_init = false;

    if (!is_init)
    {
        n = input_array_length;
        for (i = 0; i < r; i++)
            comb[i] = i;
        is_init = true;
    }
    else
    {

        i = r - 1;
        comb[i]++;
        while ((i >= 0) && (comb[i] >= n - r + 1 + i))
        {
            i--;
            comb[i]++;
        }

        if (comb[0] > n - r)
        {
            // end of current generation, we reach the end of possible combinations
            is_init = false;
            return 0;
        }

        for (i = i + 1; i < r; ++i)
            comb[i] = comb[i - 1] + 1;
    }

    for (i = 0; i < r; i++)
        next_combination_placeholder[i] = input_int_array[comb[i]];
    return 1;
}