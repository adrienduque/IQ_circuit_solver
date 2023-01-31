/**
 * @file level_data.h
 * @see level_data.c
 */

#ifndef __LEVEL_DATA_H__
#define __LEVEL_DATA_H__

#include <local/utils.h>      // Vector2_int and defines
#include <local/piece_data.h> // Tile and defines

#define MAX_NB_OF_OPEN_POINT_TILES_PER_LEVEL 6

/**
 * @struct PieceAddInfos
 * Struct to record obligatory piece hints in levels
 * infos meant to be inputs of add_piece_to_board
 */
typedef struct PieceAddInfos
{
    int piece_idx;
    int side_idx;
    Vector2_int base_pos;
    int rotation_state;

} PieceAddInfos;

/**
 * @struct LevelHints
 * Struct to record 1 level hints
 * hints can be obligatory pieces already put on the board or obligatory tiles we have to fill in with pieces
 */
typedef struct LevelHints
{
    PieceAddInfos obligatory_piece_array[NB_OF_PIECES];
    int nb_of_obligatory_pieces;
    Tile obligatory_tile_array[BOARD_TOTAL_NB_TILES];
    int nb_of_obligatory_tiles;

    int open_obligatory_point_tile_idx_array[MAX_NB_OF_OPEN_POINT_TILES_PER_LEVEL];
    int nb_of_open_obligatory_point_tiles;

} LevelHints;

LevelHints *get_level_hints(int level_num);

#endif