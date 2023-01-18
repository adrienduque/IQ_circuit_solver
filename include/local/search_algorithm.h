/**
 * @file search_algorithm.h
 * @see search_algorithm.c
 */

#ifndef __SEARCH_ALGORITHM_H__
#define __SEARCH_ALGORITHM_H__

#include <local/display.h>
#include <local/check_board.h>

#define MAX_NB_OF_COMBINATIONS 70 // There is 8 pieces that have a point, and a maximum "nCr" is obtained with 4 open points per level (nb_of_combination(set=8,subset=4) = 70)
#define MAX_NB_OF_OPEN_POINTS 6

/**
 * @struct StartCombinations
 * struct to store the different combinations of the choices we can make,
 * when we are choosing which pieces will fill the open points of the level hints
 * see search_algorithm.c description
 */
typedef struct StartCombinations
{

    int combination_array[MAX_NB_OF_COMBINATIONS][MAX_NB_OF_OPEN_POINTS];
    int nb_of_combinations;

} StartCombinations;

void run_algorithm_with_display(int level_num, double wait_seconds);

void run_algorithm_without_display(int level_num);

#endif