/**
 * @file piece_data.h
 * @see pieceçdata.c
 * Struct members might seem weird, but they all serve a purpose in later algorithms of board checking and display
 *
 */

#include <stdbool.h>
#include <local/utils.h>

#ifndef __PIECE_DATA_H__
#define __PIECE_DATA_H__

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------- Struct declarations to organize game pieces data -----------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 * @def MAX_NB_OF_SIDE_PER_PIECE
 * On the actual pieces of the game, there are a maximum of 3 playable side per piece
 * If we want to create custom pieces, we might have to change (raise) this number
 * The same applies to similar MAX macros beneath
 */
#define MAX_NB_OF_SIDE_PER_PIECE 3

#define MAX_NB_OF_TILE_PER_SIDE 4
#define MAX_NB_OF_MISSING_CONNECTION_PER_SIDE 4
#define MAX_NB_OF_BORDER_TILE_PER_SIDE 10
#define MAX_NB_OF_EDGE_POINTS 10

#define MAX_NB_OF_CONNECTION_PER_TILE 4

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
    TileType tile_type;
    RelativePos relative_pos; // relative position of tile in the definition of a side
    int flat_position;        // flatten 2D coordinates to locate on the board (initially 0)
    int nb_of_connections;    // length of matching array (initially 0)
    int connection_direction_array[MAX_NB_OF_CONNECTION_PER_TILE];
} Tile;

/**
 * @struct Side
 */
typedef struct Side
{
    int nb_of_tiles;                    // length of matching array (initially 0)
    int nb_of_missing_connection_tiles; // length of matching array (initially 0)
    int nb_of_border_tiles;             // length of matching array (initially 0)
    int nb_of_edge_points;              // length of matching array
    Tile tile_array[MAX_NB_OF_TILE_PER_SIDE];
    Tile missing_connection_tile_array[MAX_NB_OF_MISSING_CONNECTION_PER_SIDE];
    RelativePos border_tiles_rel_position_array[MAX_NB_OF_BORDER_TILE_PER_SIDE]; // not array of tiles but array of rel position of border tiles
    RelativePos outline_rel_edge_points[MAX_NB_OF_EDGE_POINTS];                  // used to draw an outline around

} Side;

/**
 * @struct Side_compute_only
 * Side members related to main computation algorithm only
 * @see place_side
 */
typedef struct Side_compute_only
{
    int nb_of_tiles;
    int nb_of_missing_connection_tiles;
    Tile tile_array[MAX_NB_OF_TILE_PER_SIDE];
    Tile missing_connection_tile_array[MAX_NB_OF_MISSING_CONNECTION_PER_SIDE];

} Side_compute_only;

/**
 * @struct Piece
 * A piece is a simple array of sides
 *
 * In the actual game pieces, there can be only one point per piece or no point at all
 * We may have to change this limitation if we want to make custom pieces
 */
typedef struct Piece
{
    int nb_of_sides; // length of matching array (initially 0)
    bool has_point_on_first_side;
    Side side_array[MAX_NB_OF_SIDE_PER_PIECE];

} Piece;

extern Piece piece_array[];

#endif