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
#define SIDE_DOESNT_FIT_INSIDE -1

int blit_side_data(Side_compute_only *side_data, Side side, int flat_base_position, int rotation_state);
void blit_border_tiles_of_side(int *border_tiles, Side side, int flat_base_position, int rotation_state);
void blit_outline_edges_points_of_side(RelativePos *outline_edge_points, Side side, int flat_base_position, int rotation_state);

#endif