/**
 * @file piece.h
 * @see piece.c
 */

#ifndef __PIECE_H__
#define __PIECE_H__

#include <local/utils.h>      // Vector2_int, helper functions
#include <local/piece_data.h> // Piece

/**
 * @note Macros meant only to be used in "blit_piece_main_data" and "can_piece_be_added_to_board" functions
 * To only have chunks of code in one place like a function definition
 * But without the hassle of copying values at runtime in functions local arguments when they would have been called
 * as the pre adding check function is the main function to be optimized to make the whole algorithm faster
 * */
#define tile_absolute_pos_computation()                            \
    do                                                             \
    {                                                              \
        current_tile->absolute_pos = current_tile->relative_pos;   \
        rotate_pos(&(current_tile->absolute_pos), rotation_state); \
        translate_pos(&(current_tile->absolute_pos), &(base_pos)); \
    } while (0)

#define tile_connection_directions_computation()                                                                                                                            \
    do                                                                                                                                                                      \
    {                                                                                                                                                                       \
        for (connection_idx = 0; connection_idx < current_tile->nb_of_connections; connection_idx++)                                                                        \
            current_tile->connection_direction_array[connection_idx] = rotate_direction(current_tile->constant_connection_direction_array[connection_idx], rotation_state); \
    } while (0)

void blit_piece_main_data(Piece *piece, int side_idx, Vector2_int base_pos, int rotation_state);
void update_piece_border_tiles(Piece *piece);

#endif