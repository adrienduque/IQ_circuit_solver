/**
 * @file check_board.h
 * @see check_board.c
 */

#ifndef __CHECK_BOARD_H__
#define __CHECK_BOARD_H__

#include <local/board.h>

#define ISOLATED_EMPTY_TILE -1
#define LOOP_PATH -2

int run_all_checks(Board *board);

#endif