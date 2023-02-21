/**
 * @author Adrien Duqué (@adrienduque)
 * Original Github repository : https://github.com/adrienduque/IQ_circuit_solver
 *
 * @file board.h
 * @see board.c
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdbool.h>
#include <stdlib.h> // NULL

#include <local/utils.h>      // defines
#include <local/piece_data.h> // Tile, Piece, and defines
#include <local/level_data.h> // LevelHints, and defines

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

    // informations inherited from level hints, useful for no dead end check (see check_board.c > "check_no_dead_ends")
    Tile *open_obligatory_point_tile_array[MAX_NB_OF_OPEN_POINT_TILES_PER_LEVEL];
    int nb_of_open_obligatory_point_tiles;

    // ------------------- Board needs pieces to work

    Piece piece_array[NB_OF_PIECES];         // all game pieces informations and their live data cache, see piece_data.h
    int added_piece_idx_array[NB_OF_PIECES]; // array of indexes of game pieces that have been added to the board
    int nb_of_added_pieces;                  // length of matching array

    // Useful information for double missing connection pre-adding check
    Vector2_int bend_double_missing_connection_position;
    Vector2_int line_double_missing_connection_position;
    bool has_T_piece_been_added;
    bool has_line2_2_been_added;
    // makes the implementation works (proxy-like variables)
    Vector2_int temp_bend_double_missing_connection_position;
    Vector2_int temp_line_double_missing_connection_position;

    // ------ Drawing data specific to the board
    Vector2 grid_lines_pt_array[NB_OF_GRID_LINES][2];
    Tile *obligatory_tile_array; // instead of finding them in obligatory tile matrix to draw them, this is a direct copy from level hints see level_data.c
    int nb_of_obligatory_tiles;

} Board;

// ------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------ Functions -------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------

// ------------- Board constructor  ----------------------------------------------------------------
Board *init_board(LevelHints *level_hints);

// ------------- main functions (add and remove pieces from board) ----------------------------------------------

// Error codes related to "can_piece_be_added_to_board" and transfered to "add_piece_to_board" (potential return values of this function)
#define OUT_OF_BOUNDS -1
#define SUPERPOSED_TILES -2
#define TILE_NOT_MATCHING_MISSING_CONNECTIONS -3
#define TILE_NOT_MATCHING_LEVEL_HINTS -4
#define TRIPLE_MISSING_CONNECTION_TILE -5
#define INVALID_DOUBLE_MISSING_CONNECTION -6

int add_piece_to_board(Board *board, int piece_idx, int side_idx, Vector2_int base_pos, int rotation_state);

void undo_last_piece_adding(Board *board);

// ------------ other public tools to interact with the board state ----------------------------------------------------
Tile *extract_normal_tile_from_stack(Tile *tile_stack);
Tile *extract_normal_tile_at_pos(Board *board, Vector2_int *base_pos);
int get_number_of_missing_connection_in_stack(Tile *tile_stack);

#endif