/**
 * @author Adrien Duqué (@adrienduque)
 * Original Github repository : https://github.com/adrienduque/IQ_circuit_solver
 *
 * @file board_save_states.h
 * @see board_save_states.c
 *
 */

#ifndef __BOARD_SAVE_STATES_H__
#define __BOARD_SAVE_STATES_H__

#include <local/piece_data.h> // NB_OF_PIECE
#include <local/level_data.h> // PieceAddInfos
#include <local/board.h>      // Board
#include <local/level_data.h> // PieceAddInfos

#define MAX_DEPTH NB_OF_PIECES
#define MAX_SAVESTATES_PER_DEPTH 1500 // level 116 is the one that required to up the value to this point

extern PieceAddInfos board_savestates[MAX_DEPTH][MAX_SAVESTATES_PER_DEPTH][NB_OF_PIECES];
extern int number_of_savestates_per_depth[MAX_DEPTH];

void init_board_savestates(void);
void save_board_state(Board *board, int current_depth);
void reset_exceeding_board_savestates(int similarity_depth);
void clean_board_pieces(Board *board);
void start_from_board_savestate(Board *board, int current_depth, int savestate_selected);
#endif