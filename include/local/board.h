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
#include <local/piece.h>
#include <local/level_data.h>

#define MAX_NB_OF_MISSING_CONNECTION_TIlES_ON_BOARD 25
#define MAX_NB_OF_DOUBLE_MISSING_CONNECTION_TIlES_ON_BOARD 2
#define NB_OF_GRID_LINES (BOARD_WIDTH + BOARD_HEIGHT + 2)

#define UNDEFINED_TILE NULL

/**
 * @struct Board
 */
typedef struct Board
{

    Tile *tile_matrix[BOARD_WIDTH][BOARD_HEIGHT];            // Matrix of Tile pointers which represents the main data of the board (array of columns), each location is now a start for a stack (history of tile superposition)
    Tile *obligatory_tile_matrix[BOARD_WIDTH][BOARD_HEIGHT]; // Matrix of Tile pointers which are part of level hints, see level_data.c

    // ------------------- Board needs pieces to work

    Piece piece_array[NB_OF_PIECES];         // all game pieces informations and their live data cache, see piece_data.h
    int added_piece_idx_array[NB_OF_PIECES]; // array of indexes of game pieces that have been added to the board
    int nb_of_added_pieces;                  // length of matching array

    bool has_line2_2_been_added;
    bool has_T_piece_been_added; // these two are special game piece, see board.c > can_piece_be_added_to_board

    // informations inherited from level hints, useful for no dead end check
    Tile *open_obligatory_point_tile_array[MAX_NB_OF_OPEN_POINT_TILES_PER_LEVEL];
    int nb_of_open_obligatory_point_tiles;

    // ------ Drawing data specific to the board
    Vector2 grid_lines_pt_array[NB_OF_GRID_LINES][2];
    Tile *obligatory_tile_array; // instead of finding them in obligatory tile matrix to draw them, it's directly a copy from level hints see level_data.c
    int nb_of_obligatory_tiles;

} Board;

// ------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------ Functions -------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------

// ------------- Board constructor / destructor ----------------------------------------------------------------
Board *init_board(LevelHints *level_hints);

// ------------- main functions (add and remove pieces from board) ----------------------------------------------

// Error codes related to "can_piece_be_added_to_board" and transfered to "add_piece_to_board"
#define OUT_OF_BOUNDS -1
#define SUPERPOSED_TILES -2
#define TILE_NOT_MATCHING_MISSING_CONNECTIONS -3
#define TILE_NOT_MATCHING_LEVEL_HINTS -4
#define TRIPLE_MISSING_CONNECTION_TILE -5
#define INVALID_DOUBLE_MISSING_CONNECTION -6

int add_piece_to_board(Board *board, int piece_idx, int side_idx, Vector2_int base_pos, int rotation_state);

void undo_last_piece_adding(Board *board);

// ------------ other public tools to interact with the board ----------------------------------------------------
Tile *extract_normal_tile_from_stack(Tile *tile_stack);
Tile *extract_normal_tile_at_pos(Board *board, Vector2_int *base_pos);

#endif