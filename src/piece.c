/**
 * @file piece.c defines the numeric model of the game puzzle pieces
 * Each piece in the game is composed of many sides, each side is composed of tiles
 * And there are a limited number of elementary tiles composing each side : point, line, bend, empty, (and missing_connection)
 * (missing_connection is a special type of tile related to the future main algorithm)
 * @see piece.h
 *
 * Here is the definition of the actual game pieces using specified structs
 * And a number of functions which apply to them
 *
 * They are separate functions as I try to compute as less as possible at each step of the process
 *
 * First of all "blit_side_data" is meant to be used as a first check to see if a piece could fit inside the board by trying to blit it at the wanted position state
 * If a piece doesn't fit, it is useless to compute other live data
 */

#include <local/piece.h>
#include <stdlib.h>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------- Main global data about game pieces ----------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

// There is a lot of data here, because I wanted to statically define them as most as it is possible, instead of them being figuring out at runtime
// In my Python prototype of this project, every side just have their normal tiles
// And there were algorithms to dynamically figure out the rest of the data, as I needed them for board checking
// I could have made algorithms that run just once and figure init data before the main loop, but manual it is

Piece piece_array[] = {
    [LINE2_1] = {
        .nb_of_sides = 3,
        .has_point_on_first_side = true,
        .side_array = {
            {
                .nb_of_tiles = 2,
                .nb_of_missing_connection_tiles = 1,
                .nb_of_border_tiles = 6,
                .nb_of_edge_points = 5,
                .tile_array = {
                    {.tile_type = point, .relative_pos = {0, 0}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}},
                    {.tile_type = bend, .relative_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {1, 1}, .nb_of_connections = 1, .connection_direction_array = {UP}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 1}},
                .outline_rel_edge_points = {{0, 0}, {2, 0}, {2, 1}, {0, 1}, {0, 0}},
            },
            {
                .nb_of_tiles = 2,
                .nb_of_missing_connection_tiles = 0,
                .nb_of_border_tiles = 6,
                .nb_of_edge_points = 5,
                .tile_array = {
                    {.tile_type = empty, .relative_pos = {0, 0}, .nb_of_connections = 0},
                    {.tile_type = empty, .relative_pos = {1, 0}, .nb_of_connections = 0},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 1}},
                .outline_rel_edge_points = {{0, 0}, {2, 0}, {2, 1}, {0, 1}, {0, 0}},
            },
            {
                .nb_of_tiles = 2,
                .nb_of_missing_connection_tiles = 2,
                .nb_of_border_tiles = 6,
                .nb_of_edge_points = 5,
                .tile_array = {
                    {.tile_type = line, .relative_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = line, .relative_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {-1, 0}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}},
                    {.tile_type = missing_connection, .relative_pos = {2, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}},

                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 1}},
                .outline_rel_edge_points = {{0, 0}, {2, 0}, {2, 1}, {0, 1}, {0, 0}},
            }}},
    [LINE2_2] = {
        .nb_of_sides = 3,
        .has_point_on_first_side = true,
        .side_array = {
            {
                .nb_of_tiles = 2,
                .nb_of_missing_connection_tiles = 1,
                .nb_of_border_tiles = 6,
                .nb_of_edge_points = 5,
                .tile_array = {
                    {.tile_type = point, .relative_pos = {0, 0}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}},
                    {.tile_type = line, .relative_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {2, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 1}},
                .outline_rel_edge_points = {{0, 0}, {2, 0}, {2, 1}, {0, 1}, {0, 0}},
            },
            {
                .nb_of_tiles = 2,
                .nb_of_missing_connection_tiles = 0,
                .nb_of_border_tiles = 6,
                .nb_of_edge_points = 5,
                .tile_array = {
                    {.tile_type = empty, .relative_pos = {0, 0}, .nb_of_connections = 0},
                    {.tile_type = empty, .relative_pos = {1, 0}, .nb_of_connections = 0},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 1}},
                .outline_rel_edge_points = {{0, 0}, {2, 0}, {2, 1}, {0, 1}, {0, 0}},
            },
            {
                .nb_of_tiles = 2,
                .nb_of_missing_connection_tiles = 2,
                .nb_of_border_tiles = 6,
                .nb_of_edge_points = 5,
                .tile_array = {
                    {.tile_type = line, .relative_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}},
                    {.tile_type = empty, .relative_pos = {1, 0}, .nb_of_connections = 0},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {0, -1}, .nb_of_connections = 1, .connection_direction_array = {DOWN}},
                    {.tile_type = missing_connection, .relative_pos = {0, 1}, .nb_of_connections = 1, .connection_direction_array = {UP}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 1}},
                .outline_rel_edge_points = {{0, 0}, {2, 0}, {2, 1}, {0, 1}, {0, 0}},
            },
        },
    },
    [LINE3_1] = {
        .nb_of_sides = 3,
        .has_point_on_first_side = true,
        .side_array = {
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 1,
                .nb_of_border_tiles = 8,
                .nb_of_edge_points = 5,
                .tile_array = {
                    {.tile_type = point, .relative_pos = {0, 0}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}},
                    {.tile_type = line, .relative_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = line, .relative_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {3, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, -1}, {3, 0}, {2, 1}, {1, 1}, {0, 1}},
                .outline_rel_edge_points = {{0, 0}, {3, 0}, {3, 1}, {0, 1}, {0, 0}},
            },
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 0,
                .nb_of_border_tiles = 8,
                .nb_of_edge_points = 5,
                .tile_array = {
                    {.tile_type = empty, .relative_pos = {0, 0}, .nb_of_connections = 0},
                    {.tile_type = empty, .relative_pos = {1, 0}, .nb_of_connections = 0},
                    {.tile_type = empty, .relative_pos = {2, 0}, .nb_of_connections = 0},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, -1}, {3, 0}, {2, 1}, {1, 1}, {0, 1}},
                .outline_rel_edge_points = {{0, 0}, {3, 0}, {3, 1}, {0, 1}, {0, 0}},
            },
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 2,
                .nb_of_border_tiles = 8,
                .nb_of_edge_points = 5,
                .tile_array = {
                    {.tile_type = line, .relative_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = line, .relative_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = bend, .relative_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {-1, 0}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}},
                    {.tile_type = missing_connection, .relative_pos = {2, -1}, .nb_of_connections = 1, .connection_direction_array = {DOWN}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, -1}, {3, 0}, {2, 1}, {1, 1}, {0, 1}},
                .outline_rel_edge_points = {{0, 0}, {3, 0}, {3, 1}, {0, 1}, {0, 0}},
            },
        },
    },
    [LINE3_2] = {
        .nb_of_sides = 3,
        .has_point_on_first_side = true,
        .side_array = {
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 1,
                .nb_of_border_tiles = 8,
                .nb_of_edge_points = 5,
                .tile_array = {
                    {.tile_type = empty, .relative_pos = {0, 0}, .nb_of_connections = 0},
                    {.tile_type = point, .relative_pos = {1, 0}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}},
                    {.tile_type = bend, .relative_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {2, -1}, .nb_of_connections = 1, .connection_direction_array = {DOWN}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, -1}, {3, 0}, {2, 1}, {1, 1}, {0, 1}},
                .outline_rel_edge_points = {{0, 0}, {3, 0}, {3, 1}, {0, 1}, {0, 0}},
            },
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 0,
                .nb_of_border_tiles = 8,
                .nb_of_edge_points = 5,
                .tile_array = {
                    {.tile_type = empty, .relative_pos = {0, 0}, .nb_of_connections = 0},
                    {.tile_type = empty, .relative_pos = {1, 0}, .nb_of_connections = 0},
                    {.tile_type = empty, .relative_pos = {2, 0}, .nb_of_connections = 0},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, -1}, {3, 0}, {2, 1}, {1, 1}, {0, 1}},
                .outline_rel_edge_points = {{0, 0}, {3, 0}, {3, 1}, {0, 1}, {0, 0}},
            },
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 2,
                .nb_of_border_tiles = 8,
                .nb_of_edge_points = 5,
                .tile_array = {
                    {.tile_type = empty, .relative_pos = {0, 0}, .nb_of_connections = 0},
                    {.tile_type = bend, .relative_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}},
                    {.tile_type = line, .relative_pos = {2, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {1, 1}, .nb_of_connections = 1, .connection_direction_array = {UP}},
                    {.tile_type = missing_connection, .relative_pos = {3, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, -1}, {3, 0}, {2, 1}, {1, 1}, {0, 1}},
                .outline_rel_edge_points = {{0, 0}, {3, 0}, {3, 1}, {0, 1}, {0, 0}},
            },
        },
    },
    [CORNER_1] = {
        .nb_of_sides = 2,
        .has_point_on_first_side = true,
        .side_array = {
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 3,
                .nb_of_border_tiles = 7,
                .nb_of_edge_points = 7,
                .tile_array = {
                    {.tile_type = point, .relative_pos = {0, 0}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}},
                    {.tile_type = line, .relative_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = line, .relative_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {1, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}},
                    {.tile_type = missing_connection, .relative_pos = {-1, 1}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}},
                    {.tile_type = missing_connection, .relative_pos = {2, 1}, .nb_of_connections = 1, .connection_direction_array = {LEFT}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, 0}, {2, 1}, {1, 2}, {0, 2}, {-1, 1}},
                .outline_rel_edge_points = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {0, 2}, {0, 0}},
            },
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 2,
                .nb_of_border_tiles = 7,
                .nb_of_edge_points = 7,
                .tile_array = {
                    {.tile_type = line, .relative_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}},
                    {.tile_type = bend, .relative_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}},
                    {.tile_type = bend, .relative_pos = {-1, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}},

                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {0, -1}, .nb_of_connections = 1, .connection_direction_array = {DOWN}},
                    {.tile_type = missing_connection, .relative_pos = {-1, 0}, .nb_of_connections = 1, .connection_direction_array = {DOWN}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, 0}, {1, 1}, {0, 2}, {-1, 2}, {-2, 1}},
                .outline_rel_edge_points = {{0, 0}, {1, 0}, {1, 2}, {-1, 2}, {-1, 1}, {0, 1}, {0, 0}},
            },
        },
    },
    [CORNER_2] = {
        .nb_of_sides = 2,
        .has_point_on_first_side = true,
        .side_array = {
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 1,
                .nb_of_border_tiles = 7,
                .nb_of_edge_points = 7,
                .tile_array = {
                    {.tile_type = point, .relative_pos = {0, 0}, .nb_of_connections = 1, .connection_direction_array = {DOWN}},
                    {.tile_type = bend, .relative_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}},
                    {.tile_type = line, .relative_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {2, 1}, .nb_of_connections = 1, .connection_direction_array = {LEFT}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, 0}, {2, 1}, {1, 2}, {0, 2}, {-1, 1}},
                .outline_rel_edge_points = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {0, 2}, {0, 0}},

            },
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 2,
                .nb_of_border_tiles = 7,
                .nb_of_edge_points = 7,
                .tile_array = {
                    {.tile_type = line, .relative_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}},
                    {.tile_type = bend, .relative_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}},
                    {.tile_type = line, .relative_pos = {-1, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {0, -1}, .nb_of_connections = 1, .connection_direction_array = {DOWN}},
                    {.tile_type = missing_connection, .relative_pos = {-2, 1}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, 0}, {1, 1}, {0, 2}, {-1, 2}, {-2, 1}},
                .outline_rel_edge_points = {{0, 0}, {1, 0}, {1, 2}, {-1, 2}, {-1, 1}, {0, 1}, {0, 0}},

            },
        },
    },
    [SQUARE] = {
        .nb_of_sides = 2,
        .has_point_on_first_side = true,
        .side_array = {
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 3,
                .nb_of_border_tiles = 8,
                .nb_of_edge_points = 5,
                .tile_array = {
                    {.tile_type = point, .relative_pos = {0, 0}, .nb_of_connections = 1, .connection_direction_array = {DOWN}},
                    {.tile_type = line, .relative_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}},
                    {.tile_type = bend, .relative_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}},
                    {.tile_type = line, .relative_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {0, 2}, .nb_of_connections = 1, .connection_direction_array = {UP}},
                    {.tile_type = missing_connection, .relative_pos = {1, 2}, .nb_of_connections = 1, .connection_direction_array = {UP}},
                    {.tile_type = missing_connection, .relative_pos = {2, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {2, 1}, {1, 2}, {0, 2}, {-1, 1}},
                .outline_rel_edge_points = {{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}},
            },
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 2,
                .nb_of_border_tiles = 8,
                .nb_of_edge_points = 5,
                .tile_array = {
                    {.tile_type = bend, .relative_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}},
                    {.tile_type = bend, .relative_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}},
                    {.tile_type = bend, .relative_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}},
                    {.tile_type = line, .relative_pos = {1, 1}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {1, -1}, .nb_of_connections = 1, .connection_direction_array = {DOWN}},
                    {.tile_type = missing_connection, .relative_pos = {2, 1}, .nb_of_connections = 1, .connection_direction_array = {LEFT}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {2, 1}, {1, 2}, {0, 2}, {-1, 1}},
                .outline_rel_edge_points = {{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}},
            },
        },
    },
    [L_PIECE] = {
        .nb_of_sides = 2,
        .has_point_on_first_side = false,
        .side_array = {
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 2,
                .nb_of_border_tiles = 9,
                .nb_of_edge_points = 7,
                .tile_array = {
                    {.tile_type = bend, .relative_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}},
                    {.tile_type = line, .relative_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}},
                    {.tile_type = bend, .relative_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, UP}},
                    {.tile_type = bend, .relative_pos = {1, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {-1, 0}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}},
                    {.tile_type = missing_connection, .relative_pos = {1, 1}, .nb_of_connections = 1, .connection_direction_array = {DOWN}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, 0}, {1, 1}, {2, 2}, {1, 3}, {0, 3}, {-1, 2}, {-1, 1}},
                .outline_rel_edge_points = {{0, 0}, {1, 0}, {1, 2}, {2, 2}, {2, 3}, {0, 3}, {0, 0}},
            },
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 2,
                .nb_of_border_tiles = 9,
                .nb_of_edge_points = 7,
                .tile_array = {
                    {.tile_type = bend, .relative_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}},
                    {.tile_type = line, .relative_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}},
                    {.tile_type = bend, .relative_pos = {0, 2}, .nb_of_connections = 2, .connection_direction_array = {LEFT, UP}},
                    {.tile_type = line, .relative_pos = {-1, 2}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {-1, 0}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}},
                    {.tile_type = missing_connection, .relative_pos = {-2, 2}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, 0}, {1, 1}, {1, 2}, {0, 3}, {-1, 3}, {-2, 2}, {-1, 1}},
                .outline_rel_edge_points = {{0, 0}, {1, 0}, {1, 3}, {-1, 3}, {-1, 2}, {0, 2}, {0, 0}},
            },
        },
    },
    [T_PIECE] = {
        .nb_of_sides = 2,
        .has_point_on_first_side = false,
        .side_array = {
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 2,
                .nb_of_border_tiles = 8,
                .nb_of_edge_points = 9,
                .tile_array = {
                    {.tile_type = bend, .relative_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}},
                    {.tile_type = bend, .relative_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}},
                    {.tile_type = line, .relative_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}},
                    {.tile_type = empty, .relative_pos = {-1, 0}, .nb_of_connections = 0},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {0, 2}, .nb_of_connections = 1, .connection_direction_array = {UP}},
                    {.tile_type = missing_connection, .relative_pos = {1, 1}, .nb_of_connections = 1, .connection_direction_array = {UP}},
                },
                .border_tiles_rel_position_array = {{-2, 0}, {-1, -1}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 2}, {-1, 1}},
                .outline_rel_edge_points = {{-1, 0}, {2, 0}, {2, 1}, {1, 1}, {1, 2}, {0, 2}, {0, 1}, {-1, 1}, {-1, 0}},
            },
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 4,
                .nb_of_border_tiles = 8,
                .nb_of_edge_points = 9,
                .tile_array = {
                    {.tile_type = line, .relative_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = line, .relative_pos = {-1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = bend, .relative_pos = {1, 0}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}},
                    {.tile_type = bend, .relative_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {1, 1}, .nb_of_connections = 1, .connection_direction_array = {UP}},
                    {.tile_type = missing_connection, .relative_pos = {0, 2}, .nb_of_connections = 1, .connection_direction_array = {UP}},
                    {.tile_type = missing_connection, .relative_pos = {-1, 1}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}},
                    {.tile_type = missing_connection, .relative_pos = {-2, 0}, .nb_of_connections = 1, .connection_direction_array = {RIGHT}},
                },
                .border_tiles_rel_position_array = {{-2, 0}, {-1, -1}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 2}, {-1, 1}},
                .outline_rel_edge_points = {{-1, 0}, {2, 0}, {2, 1}, {1, 1}, {1, 2}, {0, 2}, {0, 1}, {-1, 1}, {-1, 0}},
            },
        },
    },
    [Z_PIECE] = {
        .nb_of_sides = 2,
        .has_point_on_first_side = true,
        .side_array = {
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 1,
                .nb_of_border_tiles = 8,
                .nb_of_edge_points = 9,
                .tile_array = {
                    {.tile_type = bend, .relative_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}},
                    {.tile_type = point, .relative_pos = {1, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}},
                    {.tile_type = line, .relative_pos = {0, 1}, .nb_of_connections = 2, .connection_direction_array = {DOWN, UP}},
                    {.tile_type = empty, .relative_pos = {-1, 1}, .nb_of_connections = 0},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {0, 2}, .nb_of_connections = 1, .connection_direction_array = {UP}},
                },
                .border_tiles_rel_position_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 2}, {-1, 2}, {-2, 1}},
                .outline_rel_edge_points = {{0, 0}, {2, 0}, {2, 1}, {1, 1}, {1, 2}, {-1, 2}, {-1, 1}, {0, 1}, {0, 0}},
            },
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 2,
                .nb_of_border_tiles = 8,
                .nb_of_edge_points = 9,
                .tile_array = {
                    {.tile_type = line, .relative_pos = {0, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = bend, .relative_pos = {-1, 0}, .nb_of_connections = 2, .connection_direction_array = {RIGHT, DOWN}},
                    {.tile_type = empty, .relative_pos = {0, 1}, .nb_of_connections = 0},
                    {.tile_type = empty, .relative_pos = {1, 1}, .nb_of_connections = 0},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {-1, 1}, .nb_of_connections = 1, .connection_direction_array = {UP}},
                    {.tile_type = missing_connection, .relative_pos = {1, 0}, .nb_of_connections = 1, .connection_direction_array = {LEFT}},
                },
                .border_tiles_rel_position_array = {{-2, 0}, {-1, -1}, {0, -1}, {1, 0}, {2, 1}, {1, 2}, {0, 2}, {-1, 1}},
                .outline_rel_edge_points = {{-1, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {0, 2}, {0, 1}, {-1, 1}, {-1, 0}},
            },
        },
    },
};

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