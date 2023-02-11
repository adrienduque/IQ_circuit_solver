/**
 * @file level_data.c
 *
 * File where level hints are encoded (from level 49 to 120)
 *
 * Level hints consist of pre-added pieces on the board + or/and obligatory tiles on the board
 *
 * Expert levels (from 49 to 72  included) : board is completely filled with obligatory tiles of different types
 * Master levels (from 73 to 96  included) : board has pre-added pieces and obligatory open point tiles (point tiles that missing, but we know their numbers and positions)
 * Wizard levels (from 97 to 120 included) : board only has obligatory open point tiles
 *
 * see board.c > "init_board" function where most of the data is used
 *
 * (Data comes from my python project where I programmed a level builder, which outputs the code for corresponding level hints (+ a python script to transfer data to this project))
 *
 * (In the data we can see extra obligatory point tiles, where the pre-added pieces should go)
 * (To understand why, see board.c > "is_tile_matching_level_hints")
 * (the new open_obligatory_point_tile_idx_array contains indexes of tile in the obligatory_tile_array, that are point tiles (but only the "true" point tiles, not the extra points explained above))
 */

#include <stdlib.h> // malloc

#include <local/utils.h>      //direction defines
#include <local/piece_data.h> //Tile, defines

#include <local/level_data.h>

// Function to load level hints from the level number
LevelHints *get_level_hints(int level_num)
{
    LevelHints *level_hints = malloc(sizeof(LevelHints));

    switch (level_num)
    {
    case 49:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = bend, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {2, 1}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = line, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = line, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {0, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = line, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = line, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = bend, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = line, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = bend, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = line, .absolute_pos = {4, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = bend, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = bend, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = bend, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = line, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = line, .absolute_pos = {6, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = bend, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = bend, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = point, .absolute_pos = {6, 1}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = empty, .absolute_pos = {1, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = empty, .absolute_pos = {1, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {2, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = line, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = line, .absolute_pos = {6, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 3;
        level_hints->open_obligatory_point_tile_idx_array[1] = 24;
        level_hints->open_obligatory_point_tile_idx_array[2] = 28;
        level_hints->open_obligatory_point_tile_idx_array[3] = 31;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 50:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = bend, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = line, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = bend, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = bend, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = line, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = line, .absolute_pos = {6, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = bend, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = line, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = bend, .absolute_pos = {7, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = point, .absolute_pos = {7, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = point, .absolute_pos = {4, 0}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = line, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = line, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = empty, .absolute_pos = {5, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = empty, .absolute_pos = {6, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = empty, .absolute_pos = {5, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = empty, .absolute_pos = {4, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = empty, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = empty, .absolute_pos = {2, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = empty, .absolute_pos = {2, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = empty, .absolute_pos = {2, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = point, .absolute_pos = {1, 1}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = line, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = bend, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = bend, .absolute_pos = {0, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = line, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = line, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 13;
        level_hints->open_obligatory_point_tile_idx_array[1] = 14;
        level_hints->open_obligatory_point_tile_idx_array[2] = 15;
        level_hints->open_obligatory_point_tile_idx_array[3] = 26;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 51:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = empty, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {2, 1}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {6, 2}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = line, .absolute_pos = {6, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = bend, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = line, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = bend, .absolute_pos = {7, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = line, .absolute_pos = {6, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = bend, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = line, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = line, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = bend, .absolute_pos = {4, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = line, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = line, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = bend, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = line, .absolute_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = bend, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = bend, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = bend, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = bend, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = line, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = bend, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = empty, .absolute_pos = {0, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = empty, .absolute_pos = {0, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {1, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {5, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {5, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {5, 2}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 1;
        level_hints->open_obligatory_point_tile_idx_array[1] = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 52:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = bend, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = line, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = bend, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = bend, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = line, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = bend, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = line, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = bend, .absolute_pos = {4, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = line, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = empty, .absolute_pos = {5, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = point, .absolute_pos = {5, 2}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = bend, .absolute_pos = {6, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = line, .absolute_pos = {6, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = line, .absolute_pos = {6, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = bend, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = point, .absolute_pos = {7, 0}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = line, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = line, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = line, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {1, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {1, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {1, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {2, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 15;
        level_hints->open_obligatory_point_tile_idx_array[1] = 21;
        level_hints->open_obligatory_point_tile_idx_array[2] = 22;
        level_hints->open_obligatory_point_tile_idx_array[3] = 27;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 53:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {3, 2}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {5, 2}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = point, .absolute_pos = {6, 2}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = line, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = line, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = line, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = line, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = bend, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = bend, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = bend, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = bend, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = line, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = bend, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = line, .absolute_pos = {6, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = bend, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = line, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = bend, .absolute_pos = {7, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = empty, .absolute_pos = {5, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {5, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {4, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {1, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {1, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {1, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;
        level_hints->open_obligatory_point_tile_idx_array[4] = 4;
        level_hints->open_obligatory_point_tile_idx_array[5] = 5;

        level_hints->nb_of_open_obligatory_point_tiles = 6;
        break;
    case 54:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = bend, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = line, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = bend, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = point, .absolute_pos = {3, 2}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = line, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = line, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = bend, .absolute_pos = {0, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = bend, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = point, .absolute_pos = {1, 1}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = empty, .absolute_pos = {2, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = empty, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = point, .absolute_pos = {3, 0}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = bend, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = line, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = line, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = bend, .absolute_pos = {6, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = bend, .absolute_pos = {6, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = bend, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = bend, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = empty, .absolute_pos = {4, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = point, .absolute_pos = {7, 0}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = bend, .absolute_pos = {7, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = line, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {6, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {5, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {4, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 5;
        level_hints->open_obligatory_point_tile_idx_array[1] = 11;
        level_hints->open_obligatory_point_tile_idx_array[2] = 14;
        level_hints->open_obligatory_point_tile_idx_array[3] = 22;
        level_hints->open_obligatory_point_tile_idx_array[4] = 24;
        level_hints->open_obligatory_point_tile_idx_array[5] = 25;

        level_hints->nb_of_open_obligatory_point_tiles = 6;
        break;
    case 55:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 0}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = bend, .absolute_pos = {0, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = line, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = line, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = bend, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = line, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = bend, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = bend, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = bend, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = line, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = line, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = point, .absolute_pos = {5, 2}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = point, .absolute_pos = {4, 2}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = point, .absolute_pos = {6, 2}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = bend, .absolute_pos = {6, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = bend, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = line, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = bend, .absolute_pos = {7, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = line, .absolute_pos = {6, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = line, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = bend, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {3, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {4, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {5, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {6, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {7, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 17;
        level_hints->open_obligatory_point_tile_idx_array[2] = 18;
        level_hints->open_obligatory_point_tile_idx_array[3] = 19;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 56:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {3, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = line, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = line, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {0, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = bend, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = line, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = bend, .absolute_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = bend, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = bend, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = bend, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = bend, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = line, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = line, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = bend, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = line, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = line, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = bend, .absolute_pos = {7, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {6, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {6, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {4, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {4, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {4, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 3;
        level_hints->open_obligatory_point_tile_idx_array[1] = 15;
        level_hints->open_obligatory_point_tile_idx_array[2] = 16;
        level_hints->open_obligatory_point_tile_idx_array[3] = 26;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 57:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = line, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = bend, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = line, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = line, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = bend, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = bend, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = point, .absolute_pos = {1, 2}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = empty, .absolute_pos = {1, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = line, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = line, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = bend, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {4, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = line, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = line, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = bend, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = bend, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = line, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = line, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = bend, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = line, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = line, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {6, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {6, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 10;
        level_hints->open_obligatory_point_tile_idx_array[2] = 12;
        level_hints->open_obligatory_point_tile_idx_array[3] = 28;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 58:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {4, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = line, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = line, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = line, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = bend, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = bend, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = bend, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = line, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = bend, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = line, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = bend, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = line, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = line, .absolute_pos = {6, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = bend, .absolute_pos = {7, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = bend, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = line, .absolute_pos = {6, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = point, .absolute_pos = {5, 2}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = empty, .absolute_pos = {1, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = empty, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = empty, .absolute_pos = {1, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = empty, .absolute_pos = {2, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = empty, .absolute_pos = {5, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {6, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {7, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {7, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {6, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {5, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 21;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 59:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = empty, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = empty, .absolute_pos = {0, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = empty, .absolute_pos = {0, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = empty, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = bend, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = line, .absolute_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = line, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = bend, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = bend, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = line, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = point, .absolute_pos = {2, 1}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = line, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = line, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {4, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = bend, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = bend, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = point, .absolute_pos = {4, 2}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = empty, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = bend, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = line, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = line, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = bend, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = line, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = line, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = bend, .absolute_pos = {7, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {6, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {6, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 10;
        level_hints->open_obligatory_point_tile_idx_array[1] = 17;
        level_hints->open_obligatory_point_tile_idx_array[2] = 19;
        level_hints->open_obligatory_point_tile_idx_array[3] = 29;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 60:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 1}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {1, 1}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = bend, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = empty, .absolute_pos = {0, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = empty, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = empty, .absolute_pos = {1, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = point, .absolute_pos = {1, 3}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = bend, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = line, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = bend, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = bend, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = bend, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = empty, .absolute_pos = {3, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = empty, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = line, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = bend, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = line, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = line, .absolute_pos = {6, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = bend, .absolute_pos = {7, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = bend, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = line, .absolute_pos = {6, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = bend, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = bend, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = line, .absolute_pos = {6, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = bend, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = line, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = line, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = point, .absolute_pos = {4, 0}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 7;
        level_hints->open_obligatory_point_tile_idx_array[3] = 31;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 61:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = line, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = bend, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = line, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = bend, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = line, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = bend, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = bend, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = line, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = line, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = bend, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = line, .absolute_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = bend, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = bend, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = bend, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = bend, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = line, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = line, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = line, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = point, .absolute_pos = {5, 3}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = empty, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = empty, .absolute_pos = {6, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {6, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {0, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {4, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {4, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 24;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 62:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = bend, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = line, .absolute_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = bend, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = bend, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = bend, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = point, .absolute_pos = {3, 0}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = point, .absolute_pos = {3, 2}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = bend, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = line, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = bend, .absolute_pos = {4, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = line, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = bend, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {6, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = line, .absolute_pos = {6, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = bend, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = line, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = bend, .absolute_pos = {7, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = line, .absolute_pos = {6, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = point, .absolute_pos = {5, 3}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = empty, .absolute_pos = {0, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = empty, .absolute_pos = {0, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {2, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {2, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {4, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 8;
        level_hints->open_obligatory_point_tile_idx_array[2] = 9;
        level_hints->open_obligatory_point_tile_idx_array[3] = 24;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 63:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = bend, .absolute_pos = {0, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = bend, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = line, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = bend, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = line, .absolute_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = bend, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = line, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = line, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = line, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = bend, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = bend, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = bend, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = line, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = line, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = bend, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = line, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = point, .absolute_pos = {7, 1}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = point, .absolute_pos = {6, 1}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = line, .absolute_pos = {6, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = bend, .absolute_pos = {6, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {7, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {4, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {4, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 24;
        level_hints->open_obligatory_point_tile_idx_array[2] = 25;
        level_hints->open_obligatory_point_tile_idx_array[3] = 28;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 64:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 2}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = bend, .absolute_pos = {0, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = line, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = line, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = line, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = point, .absolute_pos = {5, 3}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = point, .absolute_pos = {1, 2}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = line, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = bend, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = bend, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = bend, .absolute_pos = {4, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = line, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = bend, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = line, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {6, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = bend, .absolute_pos = {6, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = bend, .absolute_pos = {7, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = line, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = line, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = bend, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = bend, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = point, .absolute_pos = {6, 1}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = empty, .absolute_pos = {2, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {1, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {0, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {1, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {2, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 6;
        level_hints->open_obligatory_point_tile_idx_array[2] = 7;
        level_hints->open_obligatory_point_tile_idx_array[3] = 25;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 65:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 0}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {3, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = point, .absolute_pos = {1, 2}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = bend, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {0, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = line, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = bend, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = line, .absolute_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = bend, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = bend, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = bend, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = line, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = line, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = line, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = bend, .absolute_pos = {4, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = line, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = line, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = point, .absolute_pos = {7, 1}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = empty, .absolute_pos = {5, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = empty, .absolute_pos = {6, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = empty, .absolute_pos = {5, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {6, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {7, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {5, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 3;
        level_hints->open_obligatory_point_tile_idx_array[2] = 4;
        level_hints->open_obligatory_point_tile_idx_array[3] = 23;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 66:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = bend, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = line, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = line, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = line, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = bend, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = bend, .absolute_pos = {4, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = bend, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = line, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {6, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = line, .absolute_pos = {6, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = bend, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = point, .absolute_pos = {7, 2}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = empty, .absolute_pos = {5, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = empty, .absolute_pos = {5, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = empty, .absolute_pos = {2, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = empty, .absolute_pos = {2, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = empty, .absolute_pos = {1, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = line, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = line, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = line, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {5, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 18;
        level_hints->open_obligatory_point_tile_idx_array[2] = 24;
        level_hints->open_obligatory_point_tile_idx_array[3] = 28;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 67:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {4, 0}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = line, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {7, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = line, .absolute_pos = {6, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = bend, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = line, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = bend, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = bend, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = line, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = bend, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = bend, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = line, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = line, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = bend, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = line, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = bend, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = bend, .absolute_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = line, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = point, .absolute_pos = {3, 1}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = empty, .absolute_pos = {3, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = empty, .absolute_pos = {2, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {1, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {2, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {6, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {6, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 24;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 68:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = bend, .absolute_pos = {0, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = line, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = line, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = line, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = bend, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = line, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = bend, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = bend, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = line, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = bend, .absolute_pos = {4, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = bend, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = line, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = bend, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = bend, .absolute_pos = {6, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = line, .absolute_pos = {6, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = line, .absolute_pos = {6, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = bend, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = point, .absolute_pos = {7, 2}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = empty, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {4, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {4, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {5, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {1, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {1, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 25;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 69:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 2}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = bend, .absolute_pos = {0, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = line, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = bend, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = line, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = line, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = bend, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = line, .absolute_pos = {4, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = line, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = bend, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {6, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = line, .absolute_pos = {6, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = bend, .absolute_pos = {6, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = line, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = bend, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = line, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = bend, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = point, .absolute_pos = {5, 1}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = empty, .absolute_pos = {5, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = empty, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = empty, .absolute_pos = {7, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = empty, .absolute_pos = {1, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = empty, .absolute_pos = {2, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = empty, .absolute_pos = {2, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {1, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {0, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {1, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {2, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 20;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 70:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {2, 2}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = line, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = bend, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = bend, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = line, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = line, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = line, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = bend, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = line, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = bend, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = bend, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = line, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = line, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {5, 1}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = bend, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = line, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = line, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = line, .absolute_pos = {7, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = empty, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = empty, .absolute_pos = {6, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = empty, .absolute_pos = {6, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = empty, .absolute_pos = {4, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {3, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {0, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {0, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 22;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 71:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {2, 2}, .nb_of_connections = 1, .connection_direction_array = {UP}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = line, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = bend, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = bend, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = line, .absolute_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = line, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {1, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = line, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = bend, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = line, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = line, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = bend, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = line, .absolute_pos = {4, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = line, .absolute_pos = {5, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = line, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = bend, .absolute_pos = {7, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {7, 1}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = bend, .absolute_pos = {6, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = line, .absolute_pos = {6, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = bend, .absolute_pos = {6, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = line, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = bend, .absolute_pos = {4, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = line, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = point, .absolute_pos = {4, 1}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = empty, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = empty, .absolute_pos = {7, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = empty, .absolute_pos = {5, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {5, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {0, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {0, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 23;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 72:
        level_hints->nb_of_obligatory_pieces = 0;
        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 1}, .nb_of_connections = 1, .connection_direction_array = {DOWN}};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = bend, .absolute_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = bend, .absolute_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = line, .absolute_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = bend, .absolute_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = line, .absolute_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}};
        level_hints->obligatory_tile_array[6] = (Tile){.tile_type = bend, .absolute_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[7] = (Tile){.tile_type = line, .absolute_pos = {2, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[8] = (Tile){.tile_type = line, .absolute_pos = {2, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[9] = (Tile){.tile_type = bend, .absolute_pos = {2, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[10] = (Tile){.tile_type = bend, .absolute_pos = {3, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[11] = (Tile){.tile_type = line, .absolute_pos = {3, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[12] = (Tile){.tile_type = line, .absolute_pos = {3, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[13] = (Tile){.tile_type = bend, .absolute_pos = {3, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[14] = (Tile){.tile_type = bend, .absolute_pos = {4, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[15] = (Tile){.tile_type = line, .absolute_pos = {4, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[16] = (Tile){.tile_type = bend, .absolute_pos = {4, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[17] = (Tile){.tile_type = bend, .absolute_pos = {5, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}};
        level_hints->obligatory_tile_array[18] = (Tile){.tile_type = bend, .absolute_pos = {5, 3}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}};
        level_hints->obligatory_tile_array[19] = (Tile){.tile_type = bend, .absolute_pos = {6, 3}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}};
        level_hints->obligatory_tile_array[20] = (Tile){.tile_type = line, .absolute_pos = {6, 2}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[21] = (Tile){.tile_type = line, .absolute_pos = {6, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}};
        level_hints->obligatory_tile_array[22] = (Tile){.tile_type = bend, .absolute_pos = {6, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}};
        level_hints->obligatory_tile_array[23] = (Tile){.tile_type = point, .absolute_pos = {7, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}};
        level_hints->obligatory_tile_array[24] = (Tile){.tile_type = empty, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[25] = (Tile){.tile_type = empty, .absolute_pos = {1, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[26] = (Tile){.tile_type = empty, .absolute_pos = {4, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[27] = (Tile){.tile_type = empty, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[28] = (Tile){.tile_type = empty, .absolute_pos = {7, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[29] = (Tile){.tile_type = empty, .absolute_pos = {7, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[30] = (Tile){.tile_type = empty, .absolute_pos = {5, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[31] = (Tile){.tile_type = empty, .absolute_pos = {5, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 32;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 23;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 73:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE2_1, 0, {4, 0}, 0};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){CORNER_2, 0, {3, 1}, 2};
        level_hints->obligatory_piece_array[2] = (PieceAddInfos){Z_PIECE, 0, {3, 2}, 1};
        level_hints->obligatory_piece_array[3] = (PieceAddInfos){LINE3_1, 0, {4, 3}, 0};
        level_hints->nb_of_obligatory_pieces = 4;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {4, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {3, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->nb_of_open_obligatory_point_tiles = 0;
        break;
    case 74:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE3_1, 0, {4, 0}, 2};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){SQUARE, 0, {0, 3}, 3};
        level_hints->obligatory_piece_array[2] = (PieceAddInfos){LINE2_2, 0, {3, 3}, 2};
        level_hints->obligatory_piece_array[3] = (PieceAddInfos){CORNER_1, 0, {5, 2}, 0};
        level_hints->nb_of_obligatory_pieces = 4;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {4, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {5, 2}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->nb_of_open_obligatory_point_tiles = 0;
        break;
    case 75:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE3_1, 0, {3, 3}, 2};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){CORNER_2, 0, {6, 0}, 1};
        level_hints->obligatory_piece_array[2] = (PieceAddInfos){LINE2_1, 0, {7, 3}, 2};
        level_hints->obligatory_piece_array[3] = (PieceAddInfos){LINE2_2, 0, {6, 1}, 1};
        level_hints->nb_of_obligatory_pieces = 4;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {6, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {6, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->nb_of_open_obligatory_point_tiles = 0;
        break;
    case 76:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE3_1, 0, {0, 0}, 1};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){LINE2_2, 0, {7, 0}, 2};
        level_hints->obligatory_piece_array[2] = (PieceAddInfos){LINE2_1, 0, {6, 2}, 1};
        level_hints->obligatory_piece_array[3] = (PieceAddInfos){LINE3_2, 0, {7, 3}, 3};
        level_hints->nb_of_obligatory_pieces = 4;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {7, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {6, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {7, 2}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->nb_of_open_obligatory_point_tiles = 0;
        break;
    case 77:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE3_2, 0, {5, 0}, 1};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){Z_PIECE, 0, {2, 1}, 0};
        level_hints->nb_of_obligatory_pieces = 2;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {5, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {3, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 0;
        break;
    case 78:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){CORNER_2, 0, {1, 0}, 1};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){CORNER_1, 0, {5, 1}, 2};
        level_hints->nb_of_obligatory_pieces = 2;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {5, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 0;
        break;
    case 79:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE2_1, 0, {0, 1}, 3};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){CORNER_2, 0, {0, 2}, 0};
        level_hints->obligatory_piece_array[2] = (PieceAddInfos){LINE3_2, 0, {5, 3}, 0};
        level_hints->nb_of_obligatory_pieces = 3;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {6, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {5, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {0, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = point, .absolute_pos = {0, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 6;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 3;
        break;
    case 80:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE3_1, 0, {4, 0}, 2};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){LINE2_2, 0, {0, 3}, 3};
        level_hints->obligatory_piece_array[2] = (PieceAddInfos){CORNER_1, 0, {5, 2}, 0};
        level_hints->nb_of_obligatory_pieces = 3;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {6, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {6, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {4, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = point, .absolute_pos = {5, 2}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 6;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 3;
        break;
    case 81:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){CORNER_2, 0, {1, 0}, 1};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){SQUARE, 0, {0, 3}, 3};
        level_hints->nb_of_obligatory_pieces = 2;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {1, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 82:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE2_2, 0, {3, 0}, 2};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){LINE3_1, 0, {7, 0}, 2};
        level_hints->obligatory_piece_array[2] = (PieceAddInfos){LINE3_2, 0, {3, 3}, 0};
        level_hints->nb_of_obligatory_pieces = 3;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {3, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {7, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;

        level_hints->nb_of_open_obligatory_point_tiles = 1;
        break;
    case 83:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){CORNER_1, 0, {2, 1}, 2};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){SQUARE, 0, {6, 0}, 1};
        level_hints->nb_of_obligatory_pieces = 2;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {2, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {6, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 84:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE2_1, 0, {0, 0}, 0};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){LINE3_2, 0, {0, 1}, 1};
        level_hints->obligatory_piece_array[2] = (PieceAddInfos){LINE2_2, 0, {5, 3}, 0};
        level_hints->nb_of_obligatory_pieces = 3;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = point, .absolute_pos = {0, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = point, .absolute_pos = {5, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 6;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 3;
        break;
    case 85:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){CORNER_1, 0, {1, 1}, 0};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){CORNER_2, 0, {6, 3}, 3};
        level_hints->nb_of_obligatory_pieces = 2;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {3, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {2, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {1, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 86:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE3_1, 0, {0, 0}, 1};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){LINE2_2, 0, {4, 0}, 1};
        level_hints->nb_of_obligatory_pieces = 2;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {6, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {4, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 87:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){SQUARE, 0, {7, 0}, 1};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){CORNER_2, 0, {6, 3}, 3};
        level_hints->nb_of_obligatory_pieces = 2;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {2, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {7, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 88:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){CORNER_2, 0, {1, 0}, 1};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){SQUARE, 0, {3, 3}, 3};
        level_hints->nb_of_obligatory_pieces = 2;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 0;
        break;
    case 89:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){CORNER_2, 0, {1, 0}, 1};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){CORNER_1, 0, {4, 0}, 0};
        level_hints->nb_of_obligatory_pieces = 2;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {4, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 0;
        break;
    case 90:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE2_2, 0, {3, 1}, 2};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){LINE3_1, 0, {2, 0}, 0};
        level_hints->nb_of_obligatory_pieces = 2;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {3, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {2, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 0;
        break;
    case 91:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE3_1, 0, {0, 0}, 1};
        level_hints->obligatory_piece_array[1] = (PieceAddInfos){LINE3_2, 0, {3, 3}, 0};
        level_hints->nb_of_obligatory_pieces = 2;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 0;
        break;
    case 92:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){Z_PIECE, 0, {7, 2}, 1};
        level_hints->nb_of_obligatory_pieces = 1;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {7, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {3, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {2, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 3;
        break;
    case 93:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE2_1, 0, {1, 2}, 1};
        level_hints->nb_of_obligatory_pieces = 1;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {7, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {5, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {1, 2}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 3;
        break;
    case 94:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE3_1, 0, {3, 3}, 2};
        level_hints->nb_of_obligatory_pieces = 1;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {5, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 3;
        break;
    case 95:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE3_1, 0, {0, 0}, 1};
        level_hints->nb_of_obligatory_pieces = 1;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {5, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {6, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {6, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 3;
        break;
    case 96:
        level_hints->obligatory_piece_array[0] = (PieceAddInfos){LINE2_2, 0, {0, 0}, 0};
        level_hints->nb_of_obligatory_pieces = 1;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {3, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;

        level_hints->nb_of_open_obligatory_point_tiles = 3;
        break;
    case 97:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {1, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {1, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {2, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = point, .absolute_pos = {5, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 6;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;
        level_hints->open_obligatory_point_tile_idx_array[4] = 4;
        level_hints->open_obligatory_point_tile_idx_array[5] = 5;

        level_hints->nb_of_open_obligatory_point_tiles = 6;
        break;
    case 98:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {2, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {7, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 99:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {1, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {2, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 100:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {3, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {2, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {7, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 101:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {1, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {2, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 102:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {5, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {6, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {7, 2}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 103:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {3, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {3, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 6;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;
        level_hints->open_obligatory_point_tile_idx_array[4] = 4;
        level_hints->open_obligatory_point_tile_idx_array[5] = 5;

        level_hints->nb_of_open_obligatory_point_tiles = 6;
        break;
    case 104:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {2, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {2, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {5, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = point, .absolute_pos = {6, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 6;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;
        level_hints->open_obligatory_point_tile_idx_array[4] = 4;
        level_hints->open_obligatory_point_tile_idx_array[5] = 5;

        level_hints->nb_of_open_obligatory_point_tiles = 6;
        break;
    case 105:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {2, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 106:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {2, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 2;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 107:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {3, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {5, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[4] = (Tile){.tile_type = point, .absolute_pos = {6, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[5] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 6;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;
        level_hints->open_obligatory_point_tile_idx_array[4] = 4;
        level_hints->open_obligatory_point_tile_idx_array[5] = 5;

        level_hints->nb_of_open_obligatory_point_tiles = 6;
        break;
    case 108:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {2, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {3, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {4, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {6, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 109:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {3, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {7, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 110:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {1, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {2, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {5, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 111:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {2, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {4, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {4, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 112:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {6, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {4, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {7, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 113:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {1, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {5, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {7, 1}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 114:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {2, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[2] = (Tile){.tile_type = point, .absolute_pos = {5, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[3] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 4;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;
        level_hints->open_obligatory_point_tile_idx_array[2] = 2;
        level_hints->open_obligatory_point_tile_idx_array[3] = 3;

        level_hints->nb_of_open_obligatory_point_tiles = 4;
        break;
    case 115:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {2, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 2;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 116:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {4, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 2;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 117:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {0, 0}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {6, 3}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 2;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 118:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {3, 3}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {7, 0}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 2;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 119:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {2, 1}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {4, 2}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 2;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;
    case 120:
        level_hints->nb_of_obligatory_pieces = 0;

        level_hints->obligatory_tile_array[0] = (Tile){.tile_type = point, .absolute_pos = {2, 2}, .nb_of_connections = 0};
        level_hints->obligatory_tile_array[1] = (Tile){.tile_type = point, .absolute_pos = {5, 2}, .nb_of_connections = 0};
        level_hints->nb_of_obligatory_tiles = 2;

        level_hints->open_obligatory_point_tile_idx_array[0] = 0;
        level_hints->open_obligatory_point_tile_idx_array[1] = 1;

        level_hints->nb_of_open_obligatory_point_tiles = 2;
        break;

    default:
        break;
    }

    return level_hints;
}