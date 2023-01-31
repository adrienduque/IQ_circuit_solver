/**
 * @file utils.h
 * @see utils.c
 *
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>
// --------------------------- Real game related constants -------------------

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 4
#define BOARD_TOTAL_NB_TILES 32 // BOARD_WIDTH * BOARD_HEIGHT

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

Direction reverse_direction(Direction direction);

Direction rotate_direction(Direction direction, int nb_of_clockwise_90_degres_rotation);

// --------------------------- 2D positionning stuff --------------------------

/**
 * @note i,j is the 2D position of a tile (or rather, refers to the top left corner of a tile)
 * This info is important when it comes to drawing outline of pieces
 */
typedef struct Vector2_int
{
    int i;
    int j;

} Vector2_int;

/**
 * @struct RotationMatrix
 * 2D int rotation matrix type
 */
typedef struct RotationMatrix
{

    int m0, m1;
    int m2, m3;

} RotationMatrix;

void matrix_mul(Vector2_int *pos, const RotationMatrix *matrix);

void rotate_pos(Vector2_int *pos, int rotation_state);

void translate_pos(Vector2_int *pos, const Vector2_int *translate_vector);
void increment_pos_in_direction(Vector2_int *pos, Direction direction);

bool is_pos_inside_board(const Vector2_int *pos);
bool are_pos_equal(const Vector2_int *pos1, const Vector2_int *pos2);
void set_invalid_pos(Vector2_int *pos);
bool is_pos_valid(const Vector2_int *pos);
int manhattan_dist(const Vector2_int *pos1, const Vector2_int *pos2);

// --------------------------- Math needed for main search algorithm --------------------------
int generate_next_combination(const int *input_int_array, int input_array_length, int *next_combination_placeholder, int r);

#endif