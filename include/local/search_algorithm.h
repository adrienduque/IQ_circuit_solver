/**
 * @file search_algorithm.h
 * @see search_algorithm.c
 */

#ifndef __SEARCH_ALGORITHM_H__
#define __SEARCH_ALGORITHM_H__

#define MAX_NB_OF_COMBINATIONS 70 // There is 8 pieces that have a point, and a maximum "nCr" is obtained with 4 open points per level (nb_of_combination(set=8,subset=4) = 70)

void run_algorithm_with_display(int level_num, int FPS);
void run_algorithm_without_display(int level_num);
void run_algorithm_with_extra_display(int level_num, int FPS);

#endif