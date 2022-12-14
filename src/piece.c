/**
 * @file piece.c
 * File containing functions that apply to game pieces
 *
 * They are separate functions as I try to compute as less as possible at each step of the process
 *
 * First of all "blit_side_data" is meant to be used as a first check to see if a piece could fit inside the board by trying to blit it at the wanted position state
 * If a piece doesn't fit, it is useless to compute other live datas
 */

#include <local/piece.h>

// Function to blit only side data used for main computation
// return SIDE_DOESNT_FIT_INSIDE (-1) if the side doesn't fit inside board at the wanted position state (flat_base_position,rotation_state)
// else 0
int blit_side_data(Side_compute_only *side_data, Side side, int flat_base_position, int rotation_state)
{
    // case where the side doesn't fit inside the board
    if (!is_flat_pos_valid(flat_base_position))
        return SIDE_DOESNT_FIT_INSIDE;

    side_data->nb_of_tiles = side.nb_of_tiles;
    side_data->nb_of_missing_connection_tiles = side.nb_of_missing_connection_tiles;

    RelativePos base_position = flat_pos_to_relative_pos(flat_base_position);

    Tile temp;
    for (int i = 0; i < side_data->nb_of_tiles; i++)
    {
        temp = side.tile_array[i];

        temp.flat_position = relative_pos_to_flat_pos(translate_pos(rotate_pos(temp.relative_pos, rotation_state), base_position));
        if (temp.flat_position == INVALID_FLAT_POS)
            return SIDE_DOESNT_FIT_INSIDE;
        for (int j = 0; j < temp.nb_of_connections; j++)
            temp.connection_direction_array[j] = rotate_direction(temp.connection_direction_array[j], rotation_state);

        side_data->tile_array[i] = temp;
    }
    for (int i = 0; i < side_data->nb_of_missing_connection_tiles; i++)
    {
        temp = side.missing_connection_tile_array[i];

        temp.flat_position = relative_pos_to_flat_pos(translate_pos(rotate_pos(temp.relative_pos, rotation_state), base_position));
        if (temp.flat_position == INVALID_FLAT_POS)
            return SIDE_DOESNT_FIT_INSIDE;
        for (int j = 0; j < temp.nb_of_connections; j++)
            temp.connection_direction_array[j] = rotate_direction(temp.connection_direction_array[j], rotation_state);

        side_data->missing_connection_tile_array[i] = temp;
    }
    return 0;
}

// Function to blit only border tiles of side at the right emplacement in the board
void blit_border_tiles_of_side(int *border_tiles, Side side, int flat_base_position, int rotation_state)
{
    // we assume that flat_base_position is inside board

    RelativePos base_position = flat_pos_to_relative_pos(flat_base_position);

    for (int i = 0; i < side.nb_of_border_tiles; i++)
        border_tiles[i] = relative_pos_to_flat_pos(translate_pos(rotate_pos(side.border_tiles_rel_position_array[i], rotation_state), base_position));
}

static RelativePos outline_edge_correction_values[] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};

// Function to blit only outline edge points of side at the right emplacement in the board for display
void blit_outline_edges_points_of_side(RelativePos *outline_edge_points, Side side, int flat_base_position, int rotation_state)
{
    // we assume that flat_base_position is inside board

    RelativePos base_position = flat_pos_to_relative_pos(flat_base_position);

    // why do the tile emplacements need a correction after the classic rotation / translation of relative positions ?
    // it's because the drawing function is assuming that when we pass her tile positions, we take the top-left corner of each to draw the outline
    // it will not remain true if we rotate the piece/side we want to draw.
    // for example : when we rotate 90° (: rotation_state=1), we want to take the top-right corner of each specified tile position (after classic placement computation)
    // so we take instead the top-left corner of their right neighbour (translation (1,0) for each position)

    for (int i = 0; i < side.nb_of_edge_points; i++)
        outline_edge_points[i] = translate_pos(translate_pos(rotate_pos(side.outline_rel_edge_points[i], rotation_state), base_position), outline_edge_correction_values[rotation_state]);
}