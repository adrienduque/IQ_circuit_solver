/**
 * @file piece.h
 * @see piece.c
 */

#include <local/piece_data.h>

#ifndef __PIECE_H__
#define __PIECE_H__

// BlitData is a global cache used to store current blit informations
// used to speed up operations (is there even an impact ?)
typedef struct BlitData
{
    // ----------- data set 1 time per blit
    int piece_idx;
    Piece *piece;
    int side_idx;
    Side *side;

    Vector2_int base_pos;
    int rotation_state;

} BlitData;

extern BlitData blit_data;
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Functions declarations and error codes ---------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define PIECE_DOESNT_FIT_INSIDE -1

void load_blit_data(int piece_idx, int side_idx, Vector2_int base_pos, int rotation_state);
int blit_piece_main_data(void);
void blit_border_tiles(void);
void blit_outline_tiles(void);

#endif