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
#include <local/board.h>      // Board
#include <local/level_data.h> // PieceAddInfos

#define MAX_DEPTH NB_OF_PIECES - 1
#define MAX_SAVESTATES_PER_DEPTH 32 //@todo ? // this value has to be determined by empiric experiments

void save_board_state(Board *board, int current_max_depth, PieceAddInfos board_savestates[MAX_DEPTH][MAX_SAVESTATES_PER_DEPTH][NB_OF_PIECES], int number_of_savestates_per_depth[MAX_DEPTH]);
void erase_exceeding_board_savestates(int current_max_depth, int number_of_savestates_per_depth[MAX_DEPTH]);
void start_from_board_savestate(Board *board, int current_max_depth, int savestate_selected, PieceAddInfos board_savestates[MAX_DEPTH][MAX_SAVESTATES_PER_DEPTH][NB_OF_PIECES], int trigger_piece_selected, int *piece_selected);

#endif