/**
 * @author Adrien Duqué (@adrienduque)
 * Original Github repository : https://github.com/adrienduque/IQ_circuit_solver
 *
 * @file board_save_states.c
 *
 * File that contains helper functions managing board save states (see V8)
 *
 * Used in "search_algorithm.c" and "screen_solver.c"
 */

#include <stdio.h>

#include <local/board.h>      // Board, add_piece_to_board
#include <local/level_data.h> // PieceAddInfos
#include <local/piece_data.h> // Piece and defines
#include <local/display.h>    // update_piece_all_drawing function

#include <local/board_save_states.h>

// Function to save the current board state in the board_savestates variable by reference (at current_max_depth)
void save_board_state(Board *board, int current_max_depth, PieceAddInfos board_savestates[MAX_DEPTH][MAX_SAVESTATES_PER_DEPTH][NB_OF_PIECES], int number_of_savestates_per_depth[MAX_DEPTH])
{
    static int piece_selected, piece_idx;
    static Piece *piece;
    static PieceAddInfos *piece_savestate;

    if (number_of_savestates_per_depth[current_max_depth] == MAX_SAVESTATES_PER_DEPTH - 1)
    {
        // to determine MAX_DEPTH by experiments
        printf("MAX_DEPTH is not enough ! \n");
        return;
    }

    piece_savestate = board_savestates[current_max_depth][number_of_savestates_per_depth[current_max_depth]];

    for (piece_selected = board->nb_of_level_pieces; piece_selected < current_max_depth; piece_selected++)
    {
        piece_idx = board->added_piece_idx_array[piece_selected];

        piece = (board->piece_array) + piece_idx;

        piece_savestate->piece_idx = piece_idx;
        piece_savestate->base_pos = piece->current_base_pos;
        piece_savestate->side_idx = piece->current_side_idx;
        piece_savestate->rotation_state = piece->current_rotation_state;

        piece_savestate++;
    }

    number_of_savestates_per_depth[current_max_depth]++;
}

void erase_exceeding_board_savestates(int current_max_depth, int number_of_savestates_per_depth[MAX_DEPTH])
{
    static int i;

    for (i = current_max_depth + 1; i < MAX_DEPTH; i++)
        number_of_savestates_per_depth[i] = 0;
}

// Function to initialize the board state from a previously saved savestate
// it is assumed in this function that the input is valid (/!\ to not exceed savestate_selected max value)
// trigger_piece_selected, is the value of piece_selected that is meant to trigger this function (if the algorithm backtrack enough so we can load previously computed data)
/**
 * @todo make the implementation in the main algorithm following these instructions above
 */
void start_from_board_savestate(Board *board, int current_max_depth, int savestate_selected, PieceAddInfos board_savestates[MAX_DEPTH][MAX_SAVESTATES_PER_DEPTH][NB_OF_PIECES], int trigger_piece_selected, int *next_piece_selected)
{
    static PieceAddInfos *piece_savestate;
    static int piece_selected;

    board->nb_of_added_pieces = board->nb_of_level_pieces;

    piece_savestate = board_savestates[current_max_depth][savestate_selected];

    for (piece_selected = board->nb_of_level_pieces; piece_selected < current_max_depth; piece_selected++)
    {
        add_piece_to_board(board, piece_savestate->piece_idx, piece_savestate->side_idx, piece_savestate->base_pos, piece_savestate->rotation_state);
        update_piece_all_drawing((board->piece_array) + (piece_savestate->piece_idx), false, false);
        piece_savestate++;
    }

    *next_piece_selected = trigger_piece_selected + 1;
}