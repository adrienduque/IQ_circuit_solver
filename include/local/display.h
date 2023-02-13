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

// defines for error_status, see display.c > draw_board_validation and screen_game.c
#define IDLE 0
#define ADD_SUCCESS 1
#define UNDO_SUCCESS 100
#define UNDO_ERROR 101
#define BOARD_COMPLETED 102
#define ALL_PIECE_PLAYED 103

extern const int tile_px_width;
extern const int gui_icon_scale;
extern Vector2_int offset_px;

void setup_display(int window_px_width, int window_px_height);
void setup_display_once(int window_px_width, int window_px_height);

void draw_grid();

void update_piece_all_drawing(Piece *piece, bool show_missing_connection_tiles, bool show_border_tiles);
void draw_piece(Piece *piece, bool show_missing_connection_tiles, bool show_border_tiles);

void update_board_static_drawing(Board *board);
void draw_board(Board *board, bool show_missing_connection_tiles);

void draw_level_num(int level_num);

void draw_pos_text(void);

void draw_piece_priority_array(int piece_idx_priority_array[NB_OF_PIECES], int piece_selected, int nb_of_playable_pieces, bool playable_side_per_piece_idx_mask[NB_OF_PIECES][MAX_NB_OF_SIDE_PER_PIECE]);

void draw_game_controls(void);
int draw_game_mode_choice(void);
void draw_separator(void);
int draw_FPS_choice(void);
bool draw_launch_button(void);
void draw_board_validation(int status);
void draw_solver_result(bool successful_ending, double total_time, int valid_board_count);
#endif