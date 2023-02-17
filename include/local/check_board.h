/**
 * @author Adrien Duqué (@adrienduque)
 * Original Github repository : https://github.com/adrienduque/IQ_circuit_solver
 *
 * @file check_board.h
 * @see check_board.c
 *
 * By the way,I find it funny how this module has the simplest interface, yet it contains the most important ideas and complex implementations of the whole project
 */

#ifndef __CHECK_BOARD_H__
#define __CHECK_BOARD_H__

#include <stdbool.h>

#include <local/board.h> // Board

// Error codes if a check doesn't pass, potential return values of "run_all_checks"
#define ISOLATED_EMPTY_TILE -1
#define DEAD_END -2
#define DOUBLE_MISSING_CONNECTION_NOT_FILLABLE -3
#define LOOP_PATH -4

int run_all_checks(Board *board, bool enable_not_worth_checks);

#endif