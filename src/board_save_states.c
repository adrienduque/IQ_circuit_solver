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

/**
 * @todo to release V8 :
 * - try to refactor the last changes
 * - fix update visual glitch of "draw_piece_priority_array" function with the current changes (see make run > level 104)
 * - apply the changes to the "run_algorithm_with_display" and "run_algorithm_without_display" functions
 * - apply the changes to the "screen_solver.c" file
 * - return main.c file to its normal state
 */

#include <stdio.h>

#include <local/board.h>      // Board, add_piece_to_board
#include <local/level_data.h> // PieceAddInfos
#include <local/piece_data.h> // Piece and defines
#include <local/display.h>    // update_piece_all_drawing function

#include <local/board_save_states.h>

// Module variables
PieceAddInfos board_savestates[MAX_DEPTH][MAX_SAVESTATES_PER_DEPTH][NB_OF_PIECES];
int number_of_savestates_per_depth[MAX_DEPTH];

void init_board_savestates(void)
{

    reset_exceeding_board_savestates(-1);
}

// Function to save the current board state in the board_savestates variable by reference (at current_depth)
void save_board_state(Board *board, int current_depth)
{
    static int piece_selected, piece_idx;
    static Piece *piece;
    static PieceAddInfos *piece_savestate;

    if (number_of_savestates_per_depth[current_depth] == MAX_SAVESTATES_PER_DEPTH - 1)
    {
        // to determine MAX_DEPTH by experiments
        printf("MAX_DEPTH is not enough ! \n");
        return;
    }
    piece_savestate = board_savestates[current_depth][number_of_savestates_per_depth[current_depth]];

    for (piece_selected = board->nb_of_level_pieces; piece_selected < current_depth; piece_selected++)
    {
        piece_idx = board->added_piece_idx_array[piece_selected];

        piece = (board->piece_array) + piece_idx;

        piece_savestate->piece_idx = piece_idx;
        piece_savestate->base_pos = piece->current_base_pos;
        piece_savestate->side_idx = piece->current_side_idx;
        piece_savestate->rotation_state = piece->current_rotation_state;

        piece_savestate++;
    }

    number_of_savestates_per_depth[current_depth]++;
}

void reset_exceeding_board_savestates(int similarity_depth)
{
    static int i;

    for (i = similarity_depth + 1; i < MAX_DEPTH; i++)
        number_of_savestates_per_depth[i] = 0;
}

// Function to initialize the board state from a previously saved savestate
// it is assumed in this function that the input is valid (/!\ to not exceed savestate_selected max value)
void start_from_board_savestate(Board *board, int current_depth, int savestate_selected)
{
    static PieceAddInfos *piece_savestate;
    static int piece_selected;

    clean_board_pieces(board);

    piece_savestate = board_savestates[current_depth][savestate_selected];

    for (piece_selected = board->nb_of_level_pieces; piece_selected < current_depth; piece_selected++)
    {
        add_piece_to_board(board, piece_savestate->piece_idx, piece_savestate->side_idx, piece_savestate->base_pos, piece_savestate->rotation_state);
        update_piece_all_drawing((board->piece_array) + (piece_savestate->piece_idx), false, false);
        piece_savestate++;
    }
}

void clean_board_pieces(Board *board)
{
    static int piece_idx;
    static Piece *piece;

    while (board->nb_of_added_pieces != board->nb_of_level_pieces)
    {
        undo_last_piece_adding(board);
        piece_idx = board->added_piece_idx_array[board->nb_of_added_pieces];
        piece = (board->piece_array) + piece_idx;

        piece->current_side_idx = 0;
        piece->current_base_pos.i = 0;
        piece->current_base_pos.j = 0;
        piece->current_rotation_state = 0;
    }
}