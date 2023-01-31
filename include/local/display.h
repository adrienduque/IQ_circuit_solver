/**
 * @file display.h
 * @see display.c
 */

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdbool.h>

#include <local/utils.h>      // Vector2_int
#include <local/piece_data.h> // Piece and defines
#include <local/board.h>      // Board

extern const int tile_px_width;
extern Vector2_int offset_px;

void setup_display(int window_px_width, int window_px_height);
void setup_display_once(int window_px_width, int window_px_height);

void draw_grid();

void update_piece_all_drawing(Piece *piece, bool show_missing_connection_tiles, bool show_border_tiles);
void draw_piece(Piece *piece, bool show_missing_connection_tiles, bool show_border_tiles);

void update_board_static_drawing(Board *board);
void draw_board(Board *board, bool show_missing_connection_tiles);

void draw_level_num(const char *level_num_str);

void draw_pos_text(void);

void draw_piece_priority_array(Board *board, int piece_idx_priority_array[NB_OF_PIECES], int piece_selected, int nb_of_playable_pieces, bool playable_side_per_piece_idx_mask[NB_OF_PIECES][MAX_NB_OF_SIDE_PER_PIECE]);

#endif