/**
 * @file search_algorithm.h
 * @see search_algorithm.c
 */

#ifndef __SEARCH_ALGORITHM_H__
#define __SEARCH_ALGORITHM_H__
#include <local/display.h>
#include <local/check_board.h>

#define MAX_NB_OF_COMBINATIONS 70 // There is 8 pieces that have a point, and a maximum is obtained with 4 open points per level (nb_of_combination(set=8,subset=4) = 70) "nCr"
#define MAX_NB_OF_OPEN_POINTS 6
typedef struct StartCombinations
{

    int combination_array[MAX_NB_OF_COMBINATIONS][MAX_NB_OF_OPEN_POINTS];
    int nb_of_combinations;

} StartCombinations;

void reset_all_board_pieces(Board *board);

bool run_algorithm_with_display(int level_num);

#endif