/**
 * @file display.h
 * @see display.c
 */

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdbool.h>
#include <stdio.h>
#include <raylib/raylib.h>
#include <local/utils.h>
#include <local/piece.h>
#include <local/board.h>

extern const int tile_px_width;

void setup_display(int window_px_width, int window_px_height);
void setup_display_once(int window_px_width, int window_px_height);

void draw_grid();

void update_piece_all_drawing(Piece *piece, bool show_missing_connection_tiles, bool show_border_tiles);
void draw_piece(Piece *piece, bool show_missing_connection_tiles, bool show_border_tiles);

void update_board_static_drawing(Board *board);
void draw_board(Board *board, bool show_missing_connection_tiles);

void draw_level_num(const char *level_num_str);

void draw_pos_text(void);

#endif