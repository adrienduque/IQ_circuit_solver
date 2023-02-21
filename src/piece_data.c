/**
 * @author Adrien Duqué (@adrienduque)
 * Original Github repository : https://github.com/adrienduque/IQ_circuit_solver
 *
 * @file piece_data.c defines the numeric model of the game puzzle pieces
 * Each piece in the game is composed of many sides, each side is composed of tiles
 * And there are a limited number of elementary tiles composing each side : point, line, bend, empty, (and missing_connection)
 * (missing_connection is a special type of tile related to the future main algorithm, it's like an "expected neighbour tile" type of thing)
 *
 * Other constant data is defined, which are used in the main solver algorithm like (border tiles of sides -> see check_board.c > check_isolated_tiles_around_piece function)
 * @see piece_data.h
 *
 */

#include <stdbool.h>

#include <local/piece_data.h>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------- Main global data about game pieces ----------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

// There is a lot of data here, because I wanted to statically define them as most as it is possible, instead of them being figuring out at runtime
// In my Python prototype of this project, every side just have their normal tiles
// And there were algorithms to dynamically figure out the rest of the data, as I needed them for board checking
// I could have made algorithms that run just once and figure init data before the main loop, but manual it is

void load_piece_array(Piece piece_array[NB_OF_PIECES])
{
    piece_array[LINE2_1] = (Piece){
        .name = "Line2 1",
        .has_point_on_first_side = true,
        .piece_height = 1,
        .nb_of_sides = 3,
        .nb_of_border_tiles = 6,
        .nb_of_outline_tiles = 5,
        .side_array = {
            {
                .nb_of_tiles = 2,
                .nb_of_missing_connection_tiles = 1,
                .tile_array = {
                    {.tile_type = point, .relative_pos = {0, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {RIGHT}},
                    {.tile_type = bend, .relative_pos = {1, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {1, 1}, .nb_of_connections = 1, .constant_connection_direction_array = {UP}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {2, 0}, {2, 1}, {0, 1}, {0, 0}},
                .nb_of_susceptible_loop_generator_tiles = 0,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
            {
                .nb_of_tiles = 2,
                .nb_of_missing_connection_tiles = 2,
                .tile_array = {
                    {.tile_type = line, .relative_pos = {0, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = line, .relative_pos = {1, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {-1, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {RIGHT}},
                    {.tile_type = missing_connection, .relative_pos = {2, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {LEFT}},

                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {2, 0}, {2, 1}, {0, 1}, {0, 0}},
                .susceptible_loop_generator_missing_connection_tile_idx_array = {0},
                .nb_of_susceptible_loop_generator_tiles = 1,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
            {
                .nb_of_tiles = 2,
                .nb_of_missing_connection_tiles = 0,
                .tile_array = {
                    {.tile_type = empty, .relative_pos = {0, 0}, .nb_of_connections = 0},
                    {.tile_type = empty, .relative_pos = {1, 0}, .nb_of_connections = 0},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {2, 0}, {2, 1}, {0, 1}, {0, 0}},
                .nb_of_susceptible_loop_generator_tiles = 0,
                .max_nb_of_rotations = 2,
            },
        }};

    piece_array[LINE2_2] = (Piece){
        .name = "Line2 2",
        .has_point_on_first_side = true,
        .piece_height = 1,
        .nb_of_sides = 3,
        .nb_of_border_tiles = 6,
        .nb_of_outline_tiles = 5,
        .side_array = {
            {
                .nb_of_tiles = 2,
                .nb_of_missing_connection_tiles = 1,
                .tile_array = {
                    {.tile_type = point, .relative_pos = {0, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {RIGHT}},
                    {.tile_type = line, .relative_pos = {1, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {2, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {LEFT}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {2, 0}, {2, 1}, {0, 1}, {0, 0}},
                .nb_of_susceptible_loop_generator_tiles = 0,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
            {
                .nb_of_tiles = 2,
                .nb_of_missing_connection_tiles = 2,
                .tile_array = {
                    [LINE_DOUBLE_FILLING_TILE_IDX] = {.tile_type = line, .relative_pos = {0, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, UP}},
                    {.tile_type = empty, .relative_pos = {1, 0}, .nb_of_connections = 0},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {0, -1}, .nb_of_connections = 1, .constant_connection_direction_array = {DOWN}},
                    {.tile_type = missing_connection, .relative_pos = {0, 1}, .nb_of_connections = 1, .constant_connection_direction_array = {UP}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {2, 0}, {2, 1}, {0, 1}, {0, 0}},
                .susceptible_loop_generator_missing_connection_tile_idx_array = {0},
                .nb_of_susceptible_loop_generator_tiles = 1,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
            {
                .nb_of_tiles = 2,
                .nb_of_missing_connection_tiles = 0,
                .tile_array = {
                    {.tile_type = empty, .relative_pos = {0, 0}, .nb_of_connections = 0},
                    {.tile_type = empty, .relative_pos = {1, 0}, .nb_of_connections = 0},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {2, 0}, {2, 1}, {0, 1}, {0, 0}},
                .nb_of_susceptible_loop_generator_tiles = 0,
                .max_nb_of_rotations = 2,
            },
        },
    };
    piece_array[LINE3_1] = (Piece){
        .name = "Line3 1",
        .has_point_on_first_side = true,
        .piece_height = 1,
        .nb_of_sides = 3,
        .nb_of_border_tiles = 8,
        .nb_of_outline_tiles = 5,
        .side_array = {
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 1,
                .tile_array = {
                    {.tile_type = point, .relative_pos = {0, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {RIGHT}},
                    {.tile_type = line, .relative_pos = {1, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = line, .relative_pos = {2, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {3, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {LEFT}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, -1}, {3, 0}, {2, 1}, {1, 1}, {0, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {3, 0}, {3, 1}, {0, 1}, {0, 0}},
                .nb_of_susceptible_loop_generator_tiles = 0,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 2,
                .tile_array = {
                    {.tile_type = line, .relative_pos = {0, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = line, .relative_pos = {1, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = bend, .relative_pos = {2, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {LEFT, UP}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {-1, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {RIGHT}},
                    {.tile_type = missing_connection, .relative_pos = {2, -1}, .nb_of_connections = 1, .constant_connection_direction_array = {DOWN}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, -1}, {3, 0}, {2, 1}, {1, 1}, {0, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {3, 0}, {3, 1}, {0, 1}, {0, 0}},
                .susceptible_loop_generator_missing_connection_tile_idx_array = {0},
                .nb_of_susceptible_loop_generator_tiles = 1,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 0,
                .tile_array = {
                    {.tile_type = empty, .relative_pos = {0, 0}, .nb_of_connections = 0},
                    {.tile_type = empty, .relative_pos = {1, 0}, .nb_of_connections = 0},
                    {.tile_type = empty, .relative_pos = {2, 0}, .nb_of_connections = 0},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, -1}, {3, 0}, {2, 1}, {1, 1}, {0, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {3, 0}, {3, 1}, {0, 1}, {0, 0}},
                .nb_of_susceptible_loop_generator_tiles = 0,
                .max_nb_of_rotations = 2,
            },
        },
    };
    piece_array[LINE3_2] = (Piece){
        .name = "Line3 2",
        .has_point_on_first_side = true,
        .piece_height = 1,
        .nb_of_sides = 3,
        .nb_of_border_tiles = 8,
        .nb_of_outline_tiles = 5,
        .side_array = {
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 1,
                .tile_array = {
                    {.tile_type = empty, .relative_pos = {0, 0}, .nb_of_connections = 0},
                    {.tile_type = point, .relative_pos = {1, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {RIGHT}},
                    {.tile_type = bend, .relative_pos = {2, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {LEFT, UP}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {2, -1}, .nb_of_connections = 1, .constant_connection_direction_array = {DOWN}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, -1}, {3, 0}, {2, 1}, {1, 1}, {0, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {3, 0}, {3, 1}, {0, 1}, {0, 0}},
                .nb_of_susceptible_loop_generator_tiles = 0,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 2,
                .tile_array = {
                    {.tile_type = empty, .relative_pos = {0, 0}, .nb_of_connections = 0},
                    {.tile_type = bend, .relative_pos = {1, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, DOWN}},
                    {.tile_type = line, .relative_pos = {2, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {1, 1}, .nb_of_connections = 1, .constant_connection_direction_array = {UP}},
                    {.tile_type = missing_connection, .relative_pos = {3, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {LEFT}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, -1}, {3, 0}, {2, 1}, {1, 1}, {0, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {3, 0}, {3, 1}, {0, 1}, {0, 0}},
                .susceptible_loop_generator_missing_connection_tile_idx_array = {0},
                .nb_of_susceptible_loop_generator_tiles = 1,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 0,
                .tile_array = {
                    {.tile_type = empty, .relative_pos = {0, 0}, .nb_of_connections = 0},
                    {.tile_type = empty, .relative_pos = {1, 0}, .nb_of_connections = 0},
                    {.tile_type = empty, .relative_pos = {2, 0}, .nb_of_connections = 0},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, -1}, {3, 0}, {2, 1}, {1, 1}, {0, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {3, 0}, {3, 1}, {0, 1}, {0, 0}},
                .nb_of_susceptible_loop_generator_tiles = 0,
                .max_nb_of_rotations = 2,
            },
        },
    };
    piece_array[CORNER_1] = (Piece){
        .name = "Corner 1",
        .has_point_on_first_side = true,
        .piece_height = 2,
        .nb_of_sides = 2,
        .nb_of_border_tiles = 7,
        .nb_of_outline_tiles = 7,
        .side_array = {
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 3,
                .tile_array = {
                    {.tile_type = point, .relative_pos = {0, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {RIGHT}},
                    {.tile_type = line, .relative_pos = {0, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = line, .relative_pos = {1, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {1, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {LEFT}},
                    {.tile_type = missing_connection, .relative_pos = {-1, 1}, .nb_of_connections = 1, .constant_connection_direction_array = {RIGHT}},
                    {.tile_type = missing_connection, .relative_pos = {2, 1}, .nb_of_connections = 1, .constant_connection_direction_array = {LEFT}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, 0}, {2, 1}, {1, 2}, {0, 2}, {-1, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {0, 2}, {0, 0}},
                .susceptible_loop_generator_missing_connection_tile_idx_array = {1},
                .nb_of_susceptible_loop_generator_tiles = 1,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 2,
                .tile_array = {
                    {.tile_type = line, .relative_pos = {0, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, UP}},
                    {.tile_type = bend, .relative_pos = {0, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {LEFT, UP}},
                    {.tile_type = bend, .relative_pos = {-1, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, UP}},

                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {0, -1}, .nb_of_connections = 1, .constant_connection_direction_array = {DOWN}},
                    {.tile_type = missing_connection, .relative_pos = {-1, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {DOWN}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, 0}, {1, 1}, {0, 2}, {-1, 2}, {-2, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {1, 0}, {1, 2}, {-1, 2}, {-1, 1}, {0, 1}, {0, 0}},
                .susceptible_loop_generator_missing_connection_tile_idx_array = {0},
                .nb_of_susceptible_loop_generator_tiles = 1,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
        },
    };
    piece_array[CORNER_2] = (Piece){
        .name = "Corner 2",
        .has_point_on_first_side = true,
        .piece_height = 2,
        .nb_of_sides = 2,
        .nb_of_border_tiles = 7,
        .nb_of_outline_tiles = 7,
        .side_array = {
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 1,
                .tile_array = {
                    {.tile_type = point, .relative_pos = {0, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {DOWN}},
                    {.tile_type = bend, .relative_pos = {0, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, UP}},
                    {.tile_type = line, .relative_pos = {1, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {2, 1}, .nb_of_connections = 1, .constant_connection_direction_array = {LEFT}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, 0}, {2, 1}, {1, 2}, {0, 2}, {-1, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {0, 2}, {0, 0}},
                .nb_of_susceptible_loop_generator_tiles = 0,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,

            },
            {
                .nb_of_tiles = 3,
                .nb_of_missing_connection_tiles = 2,
                .tile_array = {
                    {.tile_type = line, .relative_pos = {0, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, UP}},
                    {.tile_type = bend, .relative_pos = {0, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {LEFT, UP}},
                    {.tile_type = line, .relative_pos = {-1, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {0, -1}, .nb_of_connections = 1, .constant_connection_direction_array = {DOWN}},
                    {.tile_type = missing_connection, .relative_pos = {-2, 1}, .nb_of_connections = 1, .constant_connection_direction_array = {RIGHT}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, 0}, {1, 1}, {0, 2}, {-1, 2}, {-2, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {1, 0}, {1, 2}, {-1, 2}, {-1, 1}, {0, 1}, {0, 0}},
                .susceptible_loop_generator_missing_connection_tile_idx_array = {0},
                .nb_of_susceptible_loop_generator_tiles = 1,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
        },
    };
    piece_array[SQUARE] = (Piece){
        .name = "Square",
        .has_point_on_first_side = true,
        .piece_height = 2,
        .nb_of_sides = 2,
        .nb_of_border_tiles = 8,
        .nb_of_outline_tiles = 5,
        .side_array = {
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 3,
                .tile_array = {
                    {.tile_type = point, .relative_pos = {0, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {DOWN}},
                    {.tile_type = line, .relative_pos = {0, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, UP}},
                    {.tile_type = bend, .relative_pos = {1, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, DOWN}},
                    {.tile_type = line, .relative_pos = {1, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, UP}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {0, 2}, .nb_of_connections = 1, .constant_connection_direction_array = {UP}},
                    {.tile_type = missing_connection, .relative_pos = {1, 2}, .nb_of_connections = 1, .constant_connection_direction_array = {UP}},
                    {.tile_type = missing_connection, .relative_pos = {2, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {LEFT}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {2, 1}, {1, 2}, {0, 2}, {-1, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}},
                .susceptible_loop_generator_missing_connection_tile_idx_array = {1},
                .nb_of_susceptible_loop_generator_tiles = 1,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 2,
                .tile_array = {
                    {.tile_type = bend, .relative_pos = {1, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {LEFT, UP}},
                    {.tile_type = bend, .relative_pos = {0, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, DOWN}},
                    {.tile_type = bend, .relative_pos = {0, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, UP}},
                    {.tile_type = line, .relative_pos = {1, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {1, -1}, .nb_of_connections = 1, .constant_connection_direction_array = {DOWN}},
                    {.tile_type = missing_connection, .relative_pos = {2, 1}, .nb_of_connections = 1, .constant_connection_direction_array = {LEFT}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {2, 1}, {1, 2}, {0, 2}, {-1, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}},
                .susceptible_loop_generator_missing_connection_tile_idx_array = {0},
                .nb_of_susceptible_loop_generator_tiles = 1,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
        },
    };
    piece_array[L_PIECE] = (Piece){
        .name = "L piece",
        .has_point_on_first_side = false,
        .piece_height = 3,
        .nb_of_sides = 2,
        .nb_of_border_tiles = 9,
        .nb_of_outline_tiles = 7,
        .side_array = {
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 2,
                .tile_array = {
                    {.tile_type = bend, .relative_pos = {0, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, LEFT}},
                    {.tile_type = line, .relative_pos = {0, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, UP}},
                    {.tile_type = bend, .relative_pos = {0, 2}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, UP}},
                    {.tile_type = bend, .relative_pos = {1, 2}, .nb_of_connections = 2, .constant_connection_direction_array = {LEFT, UP}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {-1, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {RIGHT}},
                    {.tile_type = missing_connection, .relative_pos = {1, 1}, .nb_of_connections = 1, .constant_connection_direction_array = {DOWN}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, 0}, {1, 1}, {2, 2}, {1, 3}, {0, 3}, {-1, 2}, {-1, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {1, 0}, {1, 2}, {2, 2}, {2, 3}, {0, 3}, {0, 0}},
                .susceptible_loop_generator_missing_connection_tile_idx_array = {0},
                .nb_of_susceptible_loop_generator_tiles = 1,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 2,
                .tile_array = {
                    {.tile_type = bend, .relative_pos = {0, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, LEFT}},
                    {.tile_type = line, .relative_pos = {0, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, UP}},
                    {.tile_type = bend, .relative_pos = {0, 2}, .nb_of_connections = 2, .constant_connection_direction_array = {LEFT, UP}},
                    {.tile_type = line, .relative_pos = {-1, 2}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {-1, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {RIGHT}},
                    {.tile_type = missing_connection, .relative_pos = {-2, 2}, .nb_of_connections = 1, .constant_connection_direction_array = {RIGHT}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, 0}, {1, 1}, {1, 2}, {0, 3}, {-1, 3}, {-2, 2}, {-1, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {1, 0}, {1, 3}, {-1, 3}, {-1, 2}, {0, 2}, {0, 0}},
                .susceptible_loop_generator_missing_connection_tile_idx_array = {0},
                .nb_of_susceptible_loop_generator_tiles = 1,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
        },
    };
    piece_array[T_PIECE] = (Piece){
        .name = "T piece",
        .has_point_on_first_side = false,
        .piece_height = 2,
        .nb_of_sides = 2,
        .nb_of_border_tiles = 8,
        .nb_of_outline_tiles = 9,
        .side_array = {
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 2,
                .tile_array = {
                    {.tile_type = bend, .relative_pos = {0, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, DOWN}},
                    {.tile_type = bend, .relative_pos = {1, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, LEFT}},
                    {.tile_type = line, .relative_pos = {0, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, UP}},
                    {.tile_type = empty, .relative_pos = {-1, 0}, .nb_of_connections = 0},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {0, 2}, .nb_of_connections = 1, .constant_connection_direction_array = {UP}},
                    {.tile_type = missing_connection, .relative_pos = {1, 1}, .nb_of_connections = 1, .constant_connection_direction_array = {UP}},
                },
                .border_tile_relative_pos_array = {{-2, 0}, {-1, -1}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 2}, {-1, 1}},
                .outline_tile_relative_pos_array = {{-1, 0}, {2, 0}, {2, 1}, {1, 1}, {1, 2}, {0, 2}, {0, 1}, {-1, 1}, {-1, 0}},
                .susceptible_loop_generator_missing_connection_tile_idx_array = {0},
                .nb_of_susceptible_loop_generator_tiles = 1,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 4,
                .tile_array = {
                    [BEND_DOUBLE_FILLING_TILE_IDX] = {.tile_type = bend, .relative_pos = {0, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, LEFT}},
                    {.tile_type = line, .relative_pos = {0, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = line, .relative_pos = {-1, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = bend, .relative_pos = {1, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, LEFT}},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {1, 1}, .nb_of_connections = 1, .constant_connection_direction_array = {UP}},
                    {.tile_type = missing_connection, .relative_pos = {0, 2}, .nb_of_connections = 1, .constant_connection_direction_array = {UP}},
                    {.tile_type = missing_connection, .relative_pos = {-1, 1}, .nb_of_connections = 1, .constant_connection_direction_array = {RIGHT}},
                    {.tile_type = missing_connection, .relative_pos = {-2, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {RIGHT}},
                },
                .border_tile_relative_pos_array = {{-2, 0}, {-1, -1}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 2}, {-1, 1}},
                .outline_tile_relative_pos_array = {{-1, 0}, {2, 0}, {2, 1}, {1, 1}, {1, 2}, {0, 2}, {0, 1}, {-1, 1}, {-1, 0}},
                .susceptible_loop_generator_missing_connection_tile_idx_array = {0, 1},
                .nb_of_susceptible_loop_generator_tiles = 2,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
        },
    };
    piece_array[Z_PIECE] = (Piece){
        .name = "Z piece",
        .has_point_on_first_side = true,
        .piece_height = 2,
        .nb_of_sides = 2,
        .nb_of_border_tiles = 8,
        .nb_of_outline_tiles = 9,
        .side_array = {
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 1,
                .tile_array = {
                    {.tile_type = bend, .relative_pos = {0, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, DOWN}},
                    {.tile_type = point, .relative_pos = {1, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {LEFT}},
                    {.tile_type = line, .relative_pos = {0, 1}, .nb_of_connections = 2, .constant_connection_direction_array = {DOWN, UP}},
                    {.tile_type = empty, .relative_pos = {-1, 1}, .nb_of_connections = 0},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {0, 2}, .nb_of_connections = 1, .constant_connection_direction_array = {UP}},
                },
                .border_tile_relative_pos_array = {{-1, 0}, {0, -1}, {1, -1}, {2, 0}, {1, 1}, {0, 2}, {-1, 2}, {-2, 1}},
                .outline_tile_relative_pos_array = {{0, 0}, {2, 0}, {2, 1}, {1, 1}, {1, 2}, {-1, 2}, {-1, 1}, {0, 1}, {0, 0}},
                .nb_of_susceptible_loop_generator_tiles = 0,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
            {
                .nb_of_tiles = 4,
                .nb_of_missing_connection_tiles = 2,
                .tile_array = {
                    {.tile_type = line, .relative_pos = {0, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, LEFT}},
                    {.tile_type = bend, .relative_pos = {-1, 0}, .nb_of_connections = 2, .constant_connection_direction_array = {RIGHT, DOWN}},
                    {.tile_type = empty, .relative_pos = {0, 1}, .nb_of_connections = 0},
                    {.tile_type = empty, .relative_pos = {1, 1}, .nb_of_connections = 0},
                },
                .missing_connection_tile_array = {
                    {.tile_type = missing_connection, .relative_pos = {-1, 1}, .nb_of_connections = 1, .constant_connection_direction_array = {UP}},
                    {.tile_type = missing_connection, .relative_pos = {1, 0}, .nb_of_connections = 1, .constant_connection_direction_array = {LEFT}},
                },
                .border_tile_relative_pos_array = {{-2, 0}, {-1, -1}, {0, -1}, {1, 0}, {2, 1}, {1, 2}, {0, 2}, {-1, 1}},
                .outline_tile_relative_pos_array = {{-1, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {0, 2}, {0, 1}, {-1, 1}, {-1, 0}},
                .susceptible_loop_generator_missing_connection_tile_idx_array = {0},
                .nb_of_susceptible_loop_generator_tiles = 1,
                .max_nb_of_rotations = NB_OF_DIRECTIONS,
            },
        },
    };
}