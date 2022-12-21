/**
 * @file board.c
 *
 *
 */

#include <local/board.h>

void init_board(Board *board)
{

    // 1) Basic data init
    board->nb_of_missing_connection_tiles = 0;
    board->nb_of_double_missing_connection_tiles = 0;
    board->nb_of_added_pieces = 0;
    board->has_line2_2_been_added = false;
    board->has_T_piece_been_added = false;

    // 2) Set every tile pointer to UNDEFINED_TILE (NULL pointer)
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {

            board->tile_matrix[i][j] = UNDEFINED_TILE;
            board->obligatory_tile_matrix[i][j] = UNDEFINED_TILE;
        }
    }

    // 3) Get all game pieces informations and their live data cache (loading piece_array)
    board->piece_array = get_piece_array();

    // 4) Load level hints (add obligatory pieces and load obligatory tile matrix)
}

// Function to check if a piece can be added to the board while blitting its live data cache which will be used to add it
//  A piece can be added to the board if all of the beneath checks pass :
//  To every normal tile of the blitted piece :
//  * tile is not outside the board
//  * tile is not superposed to existing normal tile on the board
//  * if this tile emplacement is in the level hints (i.e. not UNDEFINED_TILE), check if the tile_type is the same (always) + connections are the same (only if the tile is not a point)
//  * if it is superposed to an existing missing_connection_tile / double missing connection tile: does the connection of the normal tile fulfill the missing connection(s)
// To every missing connection tile of the blitted piece :
// * tile is not outside the board
// * if tile is superposed to an existing normal tile -> does the connection of the normal tile fulfill the missing connection
// * tile can be superposed to another existing missing connection tile to form a double missing connection tile, if and only if special pieces containing the corresponding double connexion has not been played
// (only line2 2 has a tile that can fulfill a double missing connection in a line and only T piece has tile that can fulfill a double missing connection in a bend)
// * triple missing connection can't be valid
//
// The function discard all computations as soon as it has been detected that the piece doesn't fit and returns an error code
// else returns 1 (true)
// Let the more likely error cases be check in first to make the whole thing faster and with the less helper functions for extra speed ?
// (It doesn't matter if garbage / incomplete data is left in the piece cache, as only piece cache that had been through this function will be used in the rest of the program)
int can_piece_be_added_to_board(Board *board, int piece_idx, int side_idx, Vector2_int base_pos, int rotation_state)
{

    /**
     * @todo fonction en giga travaux, je veux essayer de faire le moins de calculs possible et les checks les plus rapide à faire en premier
     * et c'est chaud d'optimiser ça
     * je devrais sûrement faire une version non optimisée d'abord et ensuite essayer d'en faire une autre où je change l'ordre des opérations, etc
     */

    static Piece *piece = NULL;
    static Side *side = NULL;
    static Tile *current_tile = NULL;
    static Tile *existing_tile = NULL;
    static Tile *obligatory_tile = NULL;
    static int i;
    static int connection_idx;

    piece = board->piece_array + piece_idx;
    side = (piece->side_array) + side_idx;

    // ------ Normal tiles first checks -------------------
    for (i = 0; i < side->nb_of_tiles; i++)
    {
        current_tile = (side->tile_array) + i;

        // tile absolute position computation
        current_tile->absolute_pos = current_tile->relative_pos;
        rotate_pos(&(current_tile->absolute_pos), rotation_state);
        translate_pos(&(current_tile->absolute_pos), &(base_pos));

        // checks done to absolute postion of the tile
        if (!is_pos_inside_board(&(current_tile->absolute_pos)))
            return OUT_OF_BOUNDS;

        // checks done to absolute position of the tile with extra information if there is already an existing tile at this position
        existing_tile = board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j];

        if (existing_tile == UNDEFINED_TILE)
        {
            // In this case, there's no further checking as the tile in the board is free
            // connection directions still need to be computed

            // tile connection direction change computation
            for (connection_idx = 0; connection_idx < current_tile->nb_of_connections; connection_idx++)
                current_tile->connection_direction_array[connection_idx] = rotate_direction(current_tile->constant_connection_direction_array[connection_idx], rotation_state);
            continue;
        }

        if (existing_tile->tile_type != missing_connection)
            return SUPERPOSED_TILES;

        obligatory_tile = board->obligatory_tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j];

        if (obligatory_tile != UNDEFINED_TILE && current_tile->tile_type != obligatory_tile->tile_type)
            return TILE_NOT_MATCHING_LEVEL_HINTS; // if type data is not matching, neither connection directions, even without computing them

        // tile connection direction change computation
        // for further checking we need them
        for (connection_idx = 0; connection_idx < current_tile->nb_of_connections; connection_idx++)
            current_tile->connection_direction_array[connection_idx] = rotate_direction(current_tile->constant_connection_direction_array[connection_idx], rotation_state);

        if (existing_tile != UNDEFINED_TILE)
        {
            if (existing_tile->tile_type != missing_connection)
                return SUPERPOSED_TILES; // case where we try to add a normal tile where an other normal tile already exists on the board

            else
            {
                if (is_tile_matching_missing_connections(current_tile, existing_tile))
                    return TILE_NOT_MATCHING_MISSING_CONNECTIONS;
            }

            if (!is_tile_matching_level_hints(current_tile, existing_tile))
                return TILE_NOT_MATCHING_LEVEL_HINTS;
        }
    }
    //------ same for missing_connection_tiles -----------------------------
    for (i = 0; i < side->nb_of_missing_connection_tiles; i++)
    {
        // tile absolute position computation
        current_tile = (side->missing_connection_tile_array) + i;

        current_tile->absolute_pos = current_tile->relative_pos;
        rotate_pos(&(current_tile->absolute_pos), rotation_state);
        translate_pos(&(current_tile->absolute_pos), &(base_pos));

        if (!is_pos_inside_board(&(current_tile->absolute_pos)))
            return OUT_OF_BOUNDS;

        existing_tile = board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j];
        if (existing_tile != UNDEFINED_TILE)
        {
            if (existing_tile->tile_type != missing_connection)
            {
                if (is_tile_matching_missing_connections(existing_tile, current_tile))
                    return TILE_NOT_MATCHING_MISSING_CONNECTIONS;
            }

            else
            {
                /**
                 * @todo case where a missing_connection tile is going to be superposed to another one
                 */
            }
        }
    }

    //------ Normal tiles other checks --------
    for (i = 0; i < side->nb_of_tiles; i++)
    {
        current_tile = (side->tile_array) + i;
        existing_tile = board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j];
        // tile connection direction change computation
        for (connection_idx = 0; connection_idx < current_tile->nb_of_connections; connection_idx++)
            current_tile->connection_direction_array[connection_idx] = rotate_direction(current_tile->constant_connection_direction_array[connection_idx], rotation_state);
    }

    //------ same for missing_connection_tiles -----------------------------
    for (i = 0; i < side->nb_of_missing_connection_tiles; i++)
    {
        current_tile = (side->missing_connection_tile_array) + i;

        // tile connection direction change computation
        for (connection_idx = 0; connection_idx < current_tile->nb_of_connections; connection_idx++)
            current_tile->connection_direction_array[connection_idx] = rotate_direction(current_tile->constant_connection_direction_array[connection_idx], rotation_state);
    }

    piece->current_side_idx = side_idx;

    return 1; // it can be added as it has passed all the checks
}

// helper function to check if a tile respect the obligatory tile matrix which is the data of level hints
// only connection directions of obligatory tile, as type checking has already be done at this point
// see can_piece_be_added_to_board
bool is_tile_matching_connections_level_hints(Tile *current_tile, Tile *obligatory_tile)
{
    static int connection_idx;

    if (obligatory_tile->tile_type == point)
        return true; // In this case, we don't have to check the exact matching of connection directions

    for (connection_idx = 0; connection_idx < obligatory_tile->nb_of_connections; connection_idx++)
    {
        if (obligatory_tile->connection_direction_array[connection_idx] != current_tile->connection_direction_array[connection_idx])
            return false; // it is dangerous to have a fixed order check, but if I encoded all the connection direction datas correctly (by following always the same adding order (RIGHT,DOWN,LEFT,UP)), it shouldn't be an issue even with rotation_direction operation
    }
    return true;
}

// helper function to check if a normal tile connection directions fulfill the corresponding missing_connection tile ones
// see can_piece_be_added_to_board
bool is_tile_matching_missing_connections(Tile *normal_tile, Tile *missing_connection_tile)
{
    static int connection_i;
    static int connection_j;
    static Direction direction_searched_for;
    static bool direction_found;

    for (connection_i = 0; connection_i < missing_connection_tile->nb_of_connections; connection_i++)
    {
        direction_searched_for = missing_connection_tile->connection_direction_array[connection_i];
        direction_found = false;
        for (connection_j = 0; connection_j < normal_tile->nb_of_connections; connection_j++)
        {
            if (normal_tile->connection_direction_array[connection_j] == direction_searched_for)
            {
                direction_found = true;
                break;
            }
        }
        if (!direction_found)
            return false;
    }
    return true;
}

int add_piece_to_board(Board *board, int piece_idx, int side_idx, Vector2_int base_pos, int rotation_state)
{
    /**
     * @warning can_piece_be_added_to_board -> 1 is true, but -1 -2, etc are also true by default
     * don't forget to check exact return value instead of doing "if(can_piece_be_added_to_board(...)){}"
     */
}

/**
 * @todo don't forget to free(board->piece_array)
 */