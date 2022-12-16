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

#include <local/piece.h>
#include <stdlib.h>

// Function to blit only piece data used for main computation (normal and missing_connection_tile of the current side of a piece)
// and check if the piece even fit at the wanted position state
// return PIECE_DOESNT_FIT_INSIDE (-1) if the piece doesn't fit inside board at the wanted position state (flat_base_position,rotation_state)
// else 0
int blit_piece_main_data(Piece *piece_array, int piece_idx, int side_idx, Vector2_int base_pos, int rotation_state)
{
    // We assume that input data is valid and usable
    static Piece *piece = NULL;
    static Side *side = NULL;
    static Tile *current_tile = NULL;

    piece = piece_array + piece_idx;
    side = (piece->side_array) + side_idx;
    // ---------------------------------------------------------------------
    for (int i = 0; i < side->nb_of_tiles; i++)
    {
        // tile absolute position computation
        current_tile = (side->tile_array) + i;

        current_tile->absolute_pos = current_tile->relative_pos;
        rotate_pos(&(current_tile->absolute_pos), rotation_state);
        translate_pos(&(current_tile->absolute_pos), &(base_pos));
        if (!is_pos_inside_board(&(current_tile->absolute_pos)))
            return PIECE_DOESNT_FIT_INSIDE;

        // tile connection direction change computation
        for (int connection_idx = 0; connection_idx < current_tile->nb_of_connections; connection_idx++)
            current_tile->connection_direction_array[connection_idx] = rotate_direction(current_tile->constant_connection_direction_array[connection_idx], rotation_state);
    }
    //------ same for missing_connection_tiles -----------------------------
    for (int i = 0; i < side->nb_of_missing_connection_tiles; i++)
    {
        // tile absolute position computation
        current_tile = (side->missing_connection_tile_array) + i;

        current_tile->absolute_pos = current_tile->relative_pos;
        rotate_pos(&(current_tile->absolute_pos), rotation_state);
        translate_pos(&(current_tile->absolute_pos), &(base_pos));
        if (!is_pos_inside_board(&(current_tile->absolute_pos)))
            return PIECE_DOESNT_FIT_INSIDE;

        // tile connection direction change computation
        for (int connection_idx = 0; connection_idx < current_tile->nb_of_connections; connection_idx++)
            current_tile->connection_direction_array[connection_idx] = rotate_direction(current_tile->constant_connection_direction_array[connection_idx], rotation_state);
    }

    piece->current_side_idx = side_idx;

    return 0;
}

// Function to blit only border tiles of piece at the right emplacement in the board
void blit_border_tiles(Piece *piece, Vector2_int base_pos, int rotation_state)
{
    // We assume that input data is valid and usable
    static Side *side = NULL;
    side = (piece->side_array) + (piece->current_side_idx);

    static Vector2_int temp_pos;

    for (int i = 0; i < piece->nb_of_border_tiles; i++)
    {
        temp_pos = side->border_tile_relative_pos_array[i];
        rotate_pos(&temp_pos, rotation_state);
        translate_pos(&temp_pos, &(base_pos));
        if (is_pos_inside_board(&temp_pos))
            piece->border_tile_absolute_pos_array[i] = temp_pos;
        else
            set_invalid_pos(&(piece->border_tile_absolute_pos_array[i]));
    }
}

static Vector2_int outline_edge_correction_values[] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};

// Function to blit only outline edge points of side at the right emplacement in the board for display
void blit_outline_tiles(Piece *piece, Vector2_int base_pos, int rotation_state)
{
    // we assume that flat_base_position is inside board
    static Side *side = NULL;
    side = (piece->side_array) + (piece->current_side_idx);

    // why do the tile emplacements need a correction after the classic rotation / translation of relative positions ?
    // it's because the drawing function is assuming that when we pass her tile positions, we take the top-left corner of each to draw the outline edge of a piece
    // it will not remain true if we rotate the piece/side we want to draw.
    // for example : when we rotate 90° (: rotation_state=1), we want to take the top-right corner of each specified tile position (after classic placement computation)
    // so we take instead the top-left corner of their right neighbour (translation (1,0) for each position)

    static Vector2_int temp_pos_before_correction;
    for (int i = 0; i < piece->nb_of_outline_tiles; i++)
    {
        temp_pos_before_correction = side->outline_tile_relative_pos_array[i];
        rotate_pos(&temp_pos_before_correction, rotation_state);
        translate_pos(&temp_pos_before_correction, &(base_pos));

        piece->outline_tile_absolute_pos_array[i] = temp_pos_before_correction;
        translate_pos(&(piece->outline_tile_absolute_pos_array[i]), &(outline_edge_correction_values[rotation_state]));
    }
}