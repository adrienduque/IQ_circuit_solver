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

BlitData blit_data;

void load_blit_data(int piece_idx, int side_idx, Vector2_int base_pos, int rotation_state)
{
    // We assume that input data is valid and usable (0<= piece_idx < NB_OF_PIECES), (base_pos inside valid board pos), etc
    blit_data.piece_idx = piece_idx;
    blit_data.side_idx = side_idx;
    blit_data.base_pos = base_pos;
    blit_data.rotation_state = rotation_state;

    blit_data.piece = piece_array + piece_idx;
    blit_data.side = (blit_data.piece->side_array) + side_idx;

    (blit_data.piece)->current_side_idx = side_idx;
}

// Function to blit only piece data used for main computation (normal and missing_connection_tile of the current side of a piece)
// and check if the piece even fit at the wanted position state
// return PIECE_DOESNT_FIT_INSIDE (-1) if the piece doesn't fit inside board at the wanted position state (flat_base_position,rotation_state)
// else 0
int blit_piece_main_data(void)
{
    // We assume that input data is valid and usable
    static Tile *current_tile;
    // ---------------------------------------------------------------------
    for (int i = 0; i < blit_data.side->nb_of_tiles; i++)
    {
        // tile absolute position computation
        current_tile = (blit_data.side->tile_array) + i;

        current_tile->absolute_pos = current_tile->relative_pos;
        rotate_pos(&(current_tile->absolute_pos), blit_data.rotation_state);
        translate_pos(&(current_tile->absolute_pos), &(blit_data.base_pos));
        if (!is_pos_inside_board(&(current_tile->absolute_pos)))
            return PIECE_DOESNT_FIT_INSIDE;

        // tile connection direction change computation
        for (int connection_idx = 0; connection_idx < current_tile->nb_of_connections; connection_idx++)
            current_tile->connection_direction_array[connection_idx] = rotate_direction(current_tile->constant_connection_direction_array[connection_idx], blit_data.rotation_state);
    }
    //------ same for missing_connection_tiles -----------------------------
    for (int i = 0; i < blit_data.side->nb_of_missing_connection_tiles; i++)
    {
        // tile absolute position computation
        current_tile = (blit_data.side->missing_connection_tile_array) + i;

        current_tile->absolute_pos = current_tile->relative_pos;
        rotate_pos(&(current_tile->absolute_pos), blit_data.rotation_state);
        translate_pos(&(current_tile->absolute_pos), &(blit_data.base_pos));
        if (!is_pos_inside_board(&(current_tile->absolute_pos)))
            return PIECE_DOESNT_FIT_INSIDE;

        // tile connection direction change computation
        for (int connection_idx = 0; connection_idx < current_tile->nb_of_connections; connection_idx++)
            current_tile->connection_direction_array[connection_idx] = rotate_direction(current_tile->constant_connection_direction_array[connection_idx], blit_data.rotation_state);
    }

    return 0;
}

// Function to blit only border tiles of piece at the right emplacement in the board
void blit_border_tiles(void)
{
    // We assume that input data is valid and usable

    static Vector2_int temp_pos;

    for (int i = 0; i < blit_data.piece->nb_of_border_tiles; i++)
    {
        temp_pos = blit_data.side->border_tile_relative_pos_array[i];
        rotate_pos(&temp_pos, blit_data.rotation_state);
        translate_pos(&temp_pos, &(blit_data.base_pos));
        if (is_pos_inside_board(&temp_pos))
            blit_data.piece->border_tile_absolute_pos_array[i] = temp_pos;
        else
            set_invalid_pos(&(blit_data.piece->border_tile_absolute_pos_array[i]));
    }
}

static Vector2_int outline_edge_correction_values[] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};

// Function to blit only outline edge points of side at the right emplacement in the board for display
void blit_outline_tiles(void)
{
    // we assume that flat_base_position is inside board

    // why do the tile emplacements need a correction after the classic rotation / translation of relative positions ?
    // it's because the drawing function is assuming that when we pass her tile positions, we take the top-left corner of each to draw the outline edge of a piece
    // it will not remain true if we rotate the piece/side we want to draw.
    // for example : when we rotate 90° (: rotation_state=1), we want to take the top-right corner of each specified tile position (after classic placement computation)
    // so we take instead the top-left corner of their right neighbour (translation (1,0) for each position)

    static Vector2_int temp_pos_before_correction;
    for (int i = 0; i < blit_data.piece->nb_of_outline_tiles; i++)
    {
        temp_pos_before_correction = blit_data.side->outline_tile_relative_pos_array[i];
        rotate_pos(&temp_pos_before_correction, blit_data.rotation_state);
        translate_pos(&temp_pos_before_correction, &(blit_data.base_pos));

        blit_data.piece->outline_tile_absolute_pos_array[i] = temp_pos_before_correction;
        translate_pos(&(blit_data.piece->outline_tile_absolute_pos_array[i]), &(outline_edge_correction_values[blit_data.rotation_state]));
    }
}