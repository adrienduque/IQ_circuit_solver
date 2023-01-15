/**
 * @file display.h
 * @see display.c
 */

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdbool.h>
#include <raylib/raylib.h>
#include <local/utils.h>
#include <local/piece.h>
#include <local/board.h>

void setup_display();
void setup_display_once();
void DrawLineStripEx(Vector2 *points, int pointCount, float thick, Color color);

void draw_grid();
void update_board_grid_drawing(Board *board);
void draw_board_grid(Board *board);

void update_tile_drawing(Tile *tile);
void draw_tile(Tile *tile);
void draw_missing_connection_tile(Tile *tile);

void update_piece_border_tiles_drawing(Piece *piece);
void draw_piece_border_tiles(Piece *piece);

void update_piece_outline_drawing(Piece *piece);
void draw_piece_outline(Piece *piece);

// --------------------------------------------------------- Convenience functions

void update_tile_array_drawing(Tile *tile_array, int nb_of_tiles);
void draw_tile_array(Tile *tile_array, int nb_of_tiles);
void draw_missing_connection_tile_array(Tile *tile_array, int nb_of_tiles);

void update_piece_tiles_drawing(Piece *piece);
void draw_piece_tiles(Piece *piece, bool show_missing_connection_tiles);

void update_piece_all_drawing(Piece *piece, bool show_border_tiles);
void draw_piece(Piece *piece, bool show_missing_connection_tiles, bool show_border_tiles);

void update_board_obligatory_tiles_drawing(Board *board);
void draw_board(Board *board, bool show_missing_connection_tiles);

#endif