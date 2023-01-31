/**
 * @file piece.c
 * File containing functions that apply to game pieces
 *
 * They are separate functions as I try to compute as less as possible at each step of the process
 *
 * First of all "blit_piece_main_data" is meant to be used as a first check to see if a piece could fit inside the board by trying to blit it at the wanted position state
 * If a piece doesn't fit, it is useless to compute other live datas
 * Thus these functions are meant to be used in the same order as their declaration
 */

#include <stdlib.h>           // NULL
#include <local/piece_data.h> // Tile, Side, Piece

#include <local/utils.h> // Vector2_int and helper functions

#include <local/piece.h>

// Function to blit only piece data used for main computation (normal and missing_connection_tile of the current side of a piece)
// Without checks at all...
// An other function plays the same role (see board.c : "can_piece_be_added_to_board" (which is called by board.c>add_piece_to_board))
// In this later function, we try to blit the same piece data, but check a few things to say whether or not the piece can even fit in the board
void blit_piece_main_data(Piece *piece, int side_idx, Vector2_int base_pos, int rotation_state)
{
    static Side *side = NULL;
    static Tile *current_tile = NULL;
    static int i = 0;
    static int connection_idx = 0;

    side = (piece->side_array) + side_idx;

    // We need to rotate and translate each relative pos of side tiles
    // the directions of connections also change with rotation
    for (i = 0; i < side->nb_of_tiles; i++)
    {
        current_tile = (side->tile_array) + i;

        tile_absolute_pos_computation();
        tile_connection_directions_computation();
    }
    //------ same for missing_connection_tiles -----------------------------
    for (i = 0; i < side->nb_of_missing_connection_tiles; i++)
    {
        current_tile = (side->missing_connection_tile_array) + i;

        tile_absolute_pos_computation();
        tile_connection_directions_computation();
    }

    // Record of current blit inputs for the modular blit functions
    piece->current_side_idx = side_idx;
    piece->current_base_pos.i = base_pos.i;
    piece->current_base_pos.j = base_pos.j;
    piece->current_rotation_state = rotation_state;
}

// Function to blit only border tiles of piece at the right emplacement in the board
void update_piece_border_tiles(Piece *piece)
{
    static Side *side = NULL;
    static Vector2_int temp_pos;
    static int i = 0;

    side = (piece->side_array) + (piece->current_side_idx);

    for (i = 0; i < piece->nb_of_border_tiles; i++)
    {
        temp_pos = side->border_tile_relative_pos_array[i];
        rotate_pos(&temp_pos, piece->current_rotation_state);
        translate_pos(&temp_pos, &(piece->current_base_pos));
        if (is_pos_inside_board(&temp_pos))
            piece->border_tile_absolute_pos_array[i] = temp_pos;
        else
            set_invalid_pos(&(piece->border_tile_absolute_pos_array[i]));
    }
}
