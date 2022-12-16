/**
 * @file piece.h
 * @see piece.c
 */

#include <local/piece_data.h>

#ifndef __PIECE_H__
#define __PIECE_H__

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Functions declarations and error codes ---------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define PIECE_DOESNT_FIT_INSIDE -1

int blit_piece_main_data(Piece *piece_array, int piece_idx, int side_idx, Vector2_int base_pos, int rotation_state);
void blit_border_tiles(Piece *piece, Vector2_int base_pos, int rotation_state);
void blit_outline_tiles(Piece *piece, Vector2_int base_pos, int rotation_state);

#endif