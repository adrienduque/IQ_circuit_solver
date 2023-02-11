/**
 * @file piece_data.h
 * @see piece_data.c
 * Struct members might seem weird, but they all serve a purpose in later algorithms of board checking and display
 *
 */

#ifndef __PIECE_DATA_H__
#define __PIECE_DATA_H__

#include <stdbool.h>
#include <stdlib.h>

#include <raylib/raylib.h> //Vector2

#include <local/utils.h> //Vector2_int, Direction

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------- Struct declarations to organize game pieces data -----------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 * @def MAX_NB_OF_SIDE_PER_PIECE
 * On the actual pieces of the game, there are a maximum of 3 playable side per piece
 * If we want to create custom pieces, we might have to change (raise) this number
 * The same applies to similar MAX macros below
 */
#define MAX_NB_OF_SIDE_PER_PIECE 3

#define MAX_NB_OF_TILE_PER_SIDE 4
#define MAX_NB_OF_MISSING_CONNECTION_PER_SIDE 4
#define MAX_NB_OF_DISTINCT_PATH_PER_SIDE 2
#define MAX_NB_OF_BORDER_TILE_PER_SIDE 9
#define MAX_NB_OF_OUTLINE_POINTS 9

#define MAX_NB_OF_CONNECTION_PER_TILE 2

#define NB_OF_PIECES 10

/**
 * @def LINE2_1, one of many identifier of the actual game pieces
 * endoded in the form of indexes
 */
#define LINE2_1 0
#define LINE2_2 1
#define LINE3_1 2
#define LINE3_2 3
#define CORNER_1 4
#define CORNER_2 5
#define SQUARE 6
#define L_PIECE 7
#define T_PIECE 8
#define Z_PIECE 9

/**
 * @enum TileType
 * there is a limited number of elementary tiles types which are defined here
 */
typedef enum TileType
{
    point,             // point with 1 connection
    line,              // 2 connections aligned is a line
    bend,              // 2 connections at an angle is a bend
    empty,             // no connections at all, empty tile
    missing_connection // special type of tile, to tag the emplacements where a connection is expected on a side

} TileType;

/**
 * @struct Tile
 * elementary tile present in the game
 */
typedef struct Tile
{
    // ----------- Definition of a tile ----------
    TileType tile_type;
    Vector2_int relative_pos;                                               // relative position of tile in the definition of a side
    int nb_of_connections;                                                  // length of matching arrays
    int constant_connection_direction_array[MAX_NB_OF_CONNECTION_PER_TILE]; // base connections of the tile

    // ----------- Live data part -----------------

    // ------ Main
    Vector2_int absolute_pos;                                      // absolute position of the tile on the board, computed when we blit a piece to the board
    int connection_direction_array[MAX_NB_OF_CONNECTION_PER_TILE]; // connections are changed by rotation of the piece when it is blitted

    // ------ Only useful to board matrix see board.c
    struct Tile *next; // start of a stack

    // ------ Drawing data
    Vector2_int top_left_corner_pt;
    Vector2 center_pt;
    Vector2 connection_pt_array[MAX_NB_OF_CONNECTION_PER_TILE];

} Tile;

/**
 * @struct Side
 */
typedef struct Side
{
    // ----------- Definition of a side ----------
    int nb_of_tiles;                    // length of matching array
    int nb_of_missing_connection_tiles; // length of matching array
    Tile tile_array[MAX_NB_OF_TILE_PER_SIDE];
    Tile missing_connection_tile_array[MAX_NB_OF_MISSING_CONNECTION_PER_SIDE];

    // I would like to generalize below constant data, to have 1 per piece instead of 1 per side
    // but L_piece is not compatible with this design
    // the length of these arrays are common to each piece and their cache is also common to a piece instead of a side
    // see Piece::nb_of_border_tiles for example
    Vector2_int border_tile_relative_pos_array[MAX_NB_OF_BORDER_TILE_PER_SIDE]; // not array of tiles but array of relative pos of border tiles which are directly in contact with the piece (no diagonal)
    Vector2_int outline_tile_relative_pos_array[MAX_NB_OF_OUTLINE_POINTS];      // array of relative pos of tiles which have their top-left corners used to draw an outline around the piece

    // For the no loop post-adding check -> see check_board.c
    // what is contained in this array ?
    // 1) missing connection tile idx of a side, that are not directly linked to a point tile
    // 2) if 2 of these missing connection tiles pass the condition 1), but are linked together -> take only one of them
    // encoded by hand for each side of each piece
    int susceptible_loop_generator_missing_connection_tile_idx_array[MAX_NB_OF_DISTINCT_PATH_PER_SIDE];
    int nb_of_susceptible_loop_generator_tiles;

    int max_nb_of_rotations; // if we need to limit this specific this nb of rotations in the search algorithm
    // default to NB_OF_DIRECTIONS (4), but usefull if the side is symmetric, we can reduce the max_nb_of_rotations to reduce duplicate valid boards
    // for the real game pieces, Line pieces have a side full of empty tiles, we only need to test them horizontally and vertically for example

    // ----------- Live data part -----------------
    //(None until now)
} Side;

/**
 * @struct Piece
 * A piece is a simple array of sides
 *
 * @note In the actual game pieces, there can be only one point per piece or no point at all
 * We may have to change this limitation if we want to make custom pieces
 * And I always declared the side with a point first in Piece::side_array
 */
typedef struct Piece
{
    // ----------- Definition of a piece ----------
    const char *name;
    bool has_point_on_first_side;
    int piece_height;                          // vertical space taken by the piece in its default orientation (in number of tiles), useful to draw_piece_priority_array
    int nb_of_sides;                           // length of matching array
    int nb_of_border_tiles;                    // length of matching array
    int nb_of_outline_tiles;                   // length of matching array
    Side side_array[MAX_NB_OF_SIDE_PER_PIECE]; // array of sides : main data of the piece

    // ----------- Live data part -----------------

    // ------ Current blit inputs
    int current_side_idx;
    Vector2_int current_base_pos;
    int current_rotation_state;

    // ------ Savestate of the previous global position of the piece
    // (see in "run_algorithm_with_extra_display", it now has to be distinguish from current_xxx members, as these will change because of "draw_piece_priority_array")
    int test_side_idx;
    Vector2_int test_base_pos;
    int test_rotation_state;

    // ------ Cached blit results
    Vector2_int border_tile_absolute_pos_array[MAX_NB_OF_BORDER_TILE_PER_SIDE];
    Vector2_int outline_tile_absolute_pos_array[MAX_NB_OF_OUTLINE_POINTS];

    // ------ Drawing data
    Vector2_int border_tile_effective_absolute_top_left_corner_pt_array[MAX_NB_OF_BORDER_TILE_PER_SIDE];
    Vector2 outline_tile_effective_absolute_top_left_corner_pt_array[MAX_NB_OF_OUTLINE_POINTS];

} Piece;

void load_piece_array(Piece piece_array[NB_OF_PIECES]);

#endif