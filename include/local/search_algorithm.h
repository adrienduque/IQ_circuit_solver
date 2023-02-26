/**
 * @author Adrien Duqué (@adrienduque)
 * Original Github repository : https://github.com/adrienduque/IQ_circuit_solver
 *
 * @file search_algorithm.h
 * @see search_algorithm.c
 */

#ifndef __SEARCH_ALGORITHM_H__
#define __SEARCH_ALGORITHM_H__

#include <stdbool.h>

#include <local/board.h>      // Board
#include <local/utils.h>      // Vector2_int
#include <local/piece_data.h> // defines
#include <local/level_data.h> // defines

#define MAX_NB_OF_COMBINATIONS 70 // There is 8 pieces that have a point, and a maximum "nCr" is obtained with 4 open points per level (nb_of_combinations(set=8,subset=4) = 70)

/**
 * @struct StartCombinations
 * struct to store all the combinations of the different choices we can make,
 * when we are choosing which pieces will fill the open points of the level hints
 * see search_algorithm.c description
 */
typedef struct StartCombinations
{

    int combination_array[MAX_NB_OF_COMBINATIONS][MAX_NB_OF_OPEN_POINT_TILES_PER_LEVEL];
    int nb_of_combinations;

} StartCombinations;

StartCombinations determine_start_combinations(Board *board);
void load_combination_data(Board *board, StartCombinations *start_combinations, int combination_idx, int *piece_idx_priority_array, int *nb_of_playable_pieces, bool playable_side_per_piece_idx_mask[][MAX_NB_OF_SIDE_PER_PIECE]);
bool is_position_already_occupied(Board *board, Vector2_int *base_pos);

// -----------------------------------------------------------------------------

// previously used functions before the added screens.h and screen_***.c files (see main.c and raylib game templates)

void run_algorithm_with_display(int level_num, int FPS);
void run_algorithm_without_display(int level_num);
void run_algorithm_with_extra_display(int level_num, int FPS);
void run_alternative_algorithm(int level_num, int FPS);

#endif