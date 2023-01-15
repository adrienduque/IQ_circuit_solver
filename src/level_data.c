/**
 * @file level_data.c
 *
 * File where level hints are encoded (from level 49 to 120)
 * (Data comes from my python project where I programmed a level builder, which outputs the code for corresponding level hints)
 */

#include <local/level_data.h>

// Function to load level hints from the level number
// @warning @todo don't forget to limit user inputs to only implemented level numbers
LevelHints *get_level_hints(int level_num)
{
    LevelHints *level_hints = malloc(sizeof(LevelHints));

    switch (level_num)
    {

    case 83:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){4, 0, {2, 1}, 2};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){6, 0, {6, 0}, 1};
        level_hints->nb_of_obligatory_pieces = 2;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {2, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {6, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;

        /**
         * @todo don't forget to use the same priority order when encoding connection directions (RIGHT,DOWN,LEFT,UP)
         * + add extra obligatory point tiles under obligatory piece point tiles, see board.c > "is_tile_matching_level_hints"
         */

    default:
        break;
    }

    return level_hints;
}