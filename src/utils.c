/**
 * @file utils.c
 *
 * Includes all little math-like functions and macros related to positionning on the board
 * We can refer to a position on the game board, in two main ways :
 *      -by using "RelativePos" struct -> (i,j) (2D : horizontal / vertical int index of a tile)
 *      works like pixel position on a screen (j increments downwards, (0,0) is in top left corner), ...)
 *
 *          -> Used to make calculation like rotation with matrix
 *
 *      -by using 1 int index only, called "flat"
 *      works as if we had cut and put end to end every row of the game board, resulting in one line of tiles.
 *
 *          -> Used to store and iterate over all tiles of the board more easily
 *
 * Also includes helper functions for Direction type (which are encoded as int, and mainly used to specify direction of tile connections)
 */

#include <local/utils.h>

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
// (Explanation of why the data is what it is, in the comments above)
static RotationMatrix rotation_mat_array[] = {
    [RIGHT] = {1, 0, 0, 1},
    [DOWN] = {0, -1, 1, 0},
    [LEFT] = {-1, 0, 0, -1},
    [UP] = {0, 1, -1, 0},
};

RelativePos matrix_mul(RelativePos pos, RotationMatrix matrix)
{
    RelativePos result_pos;
    result_pos.i = pos.i * matrix.m0 + pos.j * matrix.m1;
    result_pos.j = pos.i * matrix.m2 + pos.j * matrix.m3;
    return result_pos;
}

RelativePos rotate_pos(RelativePos pos, int rotation_state)
{
    return matrix_mul(pos, rotation_mat_array[rotation_state]);
}

RelativePos translate_pos(RelativePos pos, RelativePos translate_vector)
{
    RelativePos result_pos;
    result_pos.i = pos.i + translate_vector.i;
    result_pos.j = pos.j + translate_vector.j;
    return result_pos;
}

// -------------------------------------- flat transformation functions ------------------------------------

// Array of increment to add to flat_position, to go right, down, left, up on the board by 1 unit
// used as a function : int next_flat_pos = flat_pos + flat_pos_direction_increment[Direction]
int flat_pos_direction_increment[] = {
    [RIGHT] = 1,
    [DOWN] = BOARD_WIDTH,
    [LEFT] = -1,
    [UP] = -BOARD_WIDTH,
};

// Function to check flat_pos validity
// i.e. : is the tile indexed by the flat pos inside the game board (valid) or not (not valid)
bool is_flat_pos_valid(int flat_pos)
{
    return (bool)((flat_pos >= 0) && (flat_pos < BOARD_TOTAL_NB_TILES));
}

// -------------------------------------- Base conversion functions ------------------------------------

int relative_pos_to_flat_pos(RelativePos pos)
{
    if (pos.i < 0 || pos.j < 0 || pos.i >= BOARD_WIDTH || pos.j >= BOARD_HEIGHT)
        return INVALID_FLAT_POS;

    // e.g : {1,2} -> 17 if BOARD_WIDTH = 8
    return pos.i + pos.j * BOARD_WIDTH;
}

RelativePos flat_pos_to_relative_pos(int flat_pos)
{
    // we assume that flat_pos is inside board and thus valid
    RelativePos result_pos;
    result_pos.j = flat_pos / BOARD_WIDTH;
    result_pos.i = flat_pos % BOARD_WIDTH;

    return result_pos;
}

// ---------------------------------------- Direction functions -------------------------------------------

// Function to reverse input direction
// e.g. : reverse_direction(RIGHT) -> LEFT
Direction reverse_direction(Direction direction_input)
{
    // they are underlying ints, see defintion of RIGHT, DOWN, ... macros in utils.h
    return (direction_input + 2) % NB_OF_DIRECTIONS;
}

// Function to rotate clockwise the input direction
// e.g. : rotate_direction(RIGHT,1) -> DOWN
// e.g. : rotate_direction(DOWN,2) == reverse_direction(DOWN) -> UP
Direction rotate_direction(Direction direction_input, int nb_of_clockwise_90_degres_rotation)
{
    // they are underlying ints, see defintion of RIGHT, DOWN, ... macros in utils.h
    return (direction_input + nb_of_clockwise_90_degres_rotation) % NB_OF_DIRECTIONS;
}
