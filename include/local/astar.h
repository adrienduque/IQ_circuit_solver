/**
 * @author Adrien Duqué (@adrienduque)
 * Original Github repository : https://github.com/adrienduque/IQ_circuit_solver
 *
 * @file astar.h
 * @see astar.c
 */

#ifndef __ASTAR_H__
#define __ASTAR_H__

#include <local/utils.h> // Vector2_int and defines
#include <local/board.h> // Board

/**
 * @struct SimpleTileTyple
 * Simpler tile representation than in piece_data.h to categorize different tiles
 * for the pathfinding algorithm
 *
 * ::no_info : we don't know what the actual tile is, but we can compute it with actual board data
 * ::clear : a tile where the pathfinding can go
 * ::wall :  a tile where the pathfinding can't go
 * ::target : clear tile + the pathfinding algorithm ends when it reaches one
 *
 * This struct is meant to be a matrix type, see SimpleTileType board_representation_matrix[BOARD_WIDTH][BOARD_HEIGHT] in check_board.c > "check_no_dead_ends"
 * It is in fact a cache shared between multiple pathfinding function calls, computed as the pathfinding goes through "no_info" tiles, it explores the current board state as it needs
 */
typedef enum SimpleTileType
{
    no_info,
    clear,
    wall,
    target,

} SimpleTileType;

Tile *find_a_path(Board *board, Vector2_int *start_pos, Vector2_int *target_pos, SimpleTileType board_representation_matrix[BOARD_WIDTH][BOARD_HEIGHT]);

#endif