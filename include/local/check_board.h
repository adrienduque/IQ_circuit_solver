/**
 * @file check_board.h
 * @see check_board.c
 */

#ifndef __CHECK_BOARD_H__
#define __CHECK_BOARD_H__

#include <stdbool.h>

#include <local/board.h> // Board

#define ISOLATED_EMPTY_TILE -1
#define DEAD_END -2
#define DOUBLE_MISSING_CONNECTION_NOT_FILLABLE -3
#define LOOP_PATH -4

int run_all_checks(Board *board, bool enable_not_worth_checks);

#endif