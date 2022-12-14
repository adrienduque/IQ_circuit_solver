/**
 * @file piece_data.c defines the numeric model of the game puzzle pieces
 * Each piece in the game is composed of many sides, each side is composed of tiles
 * And there are a limited number of elementary tiles composing each side : point, line, bend, empty, (and missing_connection)
 * (missing_connection is a special type of tile related to the future main algorithm)
 *
 * Other constant data is defined, which will be useful in the main algorithm like (border tiles of sides, edge points, ...)
 *
 * @see piece_data.h
 *
 */

#include <local/piece_data.h>
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
