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
void DrawLineStripEx(Vector2 *points, int pointCount, float thick, Color color);

void draw_grid();
void load_draw_grid_data(Board *board);
void draw_board_grid(Board *board);

void load_draw_tile_data(Tile *tile);
void draw_tile(Tile *tile);
void draw_missing_connection_tile(Tile *tile);

void load_draw_border_tile_data(Piece *piece);
void draw_border_tiles(Piece *piece);

void load_draw_outline_tile_data(Piece *piece);
void draw_outline_edge_points(Piece *piece);

void update_all_piece_draw_data(Piece *piece, bool show_missing_connection_tiles, bool show_border_tiles);
void draw_all_piece_data(Piece *piece, bool show_missing_connection_tiles, bool show_border_tiles);

#endif