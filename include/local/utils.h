/**
 * @file utils.h
 * @see utils.c
 *
 */

#include <stdbool.h>

#ifndef __UTILS_H__
#define __UTILS_H__

// --------------------------- Real game related constants -------------------

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 4
#define BOARD_TOTAL_NB_TILES 32 // BOARD_WIDTH * BOARD_HEIGHT

// --------------------------- 2D positionning stuff --------------------------

/**
 * @note i,j is the 2D position of a tile (or rather, refers to the top left corner of a tile)
 * This info is important when it comes to drawing outline of pieces
 */
typedef struct RelativePos
{
    int i;
    int j;

} RelativePos;

/**
 * @struct RotationMatrix
 * 2D int rotation matrix type
 */
typedef struct RotationMatrix
{

    int m0, m1;
    int m2, m3;

} RotationMatrix;

RelativePos matrix_mul(RelativePos pos, RotationMatrix matrix);

RelativePos rotate_pos(RelativePos pos, int rotation_state);

RelativePos translate_pos(RelativePos pos, RelativePos translate_vector);

// --------------------------- flat positionning stuff ------------------------
#define INVALID_FLAT_POS -1
extern int flat_pos_direction_increment[];
bool is_flat_pos_valid(int flat_pos);

// --------------------------- base conversion functions ----------------------

int relative_pos_to_flat_pos(RelativePos pos);
RelativePos flat_pos_to_relative_pos(int flat_pos);

// --------------------------- direction encoding stuff -----------------------

#define NB_OF_DIRECTIONS 4
typedef int Direction;

/**
 * @def RIGHT
 * one of the definitions of 4 elementary directions, encoded as int indexes starting from 0 and increasing clockwise
 */
#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

Direction reverse_direction(Direction direction_input);

Direction rotate_direction(Direction direction_input, int nb_of_right_rotation);

#endif