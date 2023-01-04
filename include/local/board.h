/**
 * @file board.h
 * @see board.c
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdlib.h>
#include <math.h>
#include <local/utils.h>
#include <local/piece_data.h>

#define MAX_NB_OF_MISSING_CONNECTION_TIlES_ON_BOARD 25
#define NB_OF_GRID_LINES (BOARD_WIDTH + BOARD_HEIGHT + 2)

#define UNDEFINED_TILE NULL

#define MAX_NB_OF_DOUBLE_MISSING_CONNECTION_TILES_ON_BOARD 2
// statically defined indexes for created_double_missing_connection_tile_array
#define LINE_SHAPE_IDX 0
#define BEND_SHAPE_IDX 1

typedef struct Board
{
    Tile *tile_matrix[BOARD_WIDTH][BOARD_HEIGHT];            // Matrix of Tile pointers which represents the main data of the board (array of columns)
    Tile *obligatory_tile_matrix[BOARD_WIDTH][BOARD_HEIGHT]; // Matrix of Tile pointers which will be the selected level hints @todo change desc when I add level.c
    Piece *piece_array;                                      // all game pieces informations and their live data cache, see piece_data.h

    Tile *missing_connection_tile_array[MAX_NB_OF_MISSING_CONNECTION_TIlES_ON_BOARD]; // to find them in tile_matrix
    int nb_of_missing_connection_tiles;                                               // length of matching array (Missing connection tiles are treated separately to access them more easily)

    Tile *double_missing_connection_tile_array[MAX_NB_OF_DOUBLE_MISSING_CONNECTION_TILES_ON_BOARD]; //
    int added_piece_idx_array[NB_OF_PIECES];                                                        // array of indexes of game pieces that have been added to the board
    int nb_of_added_pieces;                                                                         // length of matching array

    // -----------------------------
    Tile *created_double_missing_connection_tile_array[MAX_NB_OF_DOUBLE_MISSING_CONNECTION_TILES_ON_BOARD]; // array of pointers to be allocated when a tile with a double missing connection is created (I have to link their memory to the board as this is a result of a superposition of 2 missing connection tile, I don't want to modifiy missing connection tiles of pieces)
    bool has_line2_2_been_added;
    bool has_T_piece_been_added; // these two are special game piece, see board.c > can_piece_be_added_to_board

    // ----------------------------- Last piece added informations needed to revert the addition

    // ------ Drawing data
    Vector2 grid_lines_pt_array[NB_OF_GRID_LINES][2];

} Board;

// ------------- Board constructor / destructor
Board *init_board();
void free_board(Board *board);

// ------------- pre-adding public checks
bool is_position_already_occupied(Board *board, Vector2_int base_pos);

// ------------- main functions (add and remove pieces from board)
#define OUT_OF_BOUNDS -1
#define SUPERPOSED_TILES -2
#define TILE_NOT_MATCHING_MISSING_CONNECTIONS -3
#define TILE_NOT_MATCHING_LEVEL_HINTS -4
#define TRIPLE_MISSING_CONNECTION_TILE -5
#define INVALID_DOUBLE_MISSING_CONNECTION -6

bool add_piece_to_board(Board *board, int piece_idx, int side_idx, Vector2_int base_pos, int rotation_state);

// ------------- post-adding public checks

#endif