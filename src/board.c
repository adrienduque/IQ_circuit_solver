/**
 * @file board.c
 *
 * @todo let's draw it and do unit testing before adding more code
 */

#include <local/board.h>

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------- Board constructor / destructor ------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Board *init_board()
{
    Board *board = malloc(sizeof(Board));

    // 1) Basic data init
    board->nb_of_missing_connection_tiles = 0;
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
    for (int i = 0; i < MAX_NB_OF_MISSING_CONNECTION_TIlES_ON_BOARD; i++)
        board->missing_connection_tile_array[i] = UNDEFINED_TILE;

    for (int i = 0; i < MAX_NB_OF_DOUBLE_MISSING_CONNECTION_TILES_ON_BOARD; i++)
        board->double_missing_connection_tile_array[i] = UNDEFINED_TILE;

    board->created_double_missing_connection_tile_array[LINE_SHAPE_IDX] = calloc(1, sizeof(Tile));
    board->created_double_missing_connection_tile_array[BEND_SHAPE_IDX] = calloc(1, sizeof(Tile));

    // 3) Get all game pieces informations and their live data cache (loading piece_array)
    board->piece_array = get_piece_array();

    // 4) Load level hints (add obligatory pieces and load obligatory tile matrix)

    return board;
}

void free_board(Board *board)
{
    free(board->piece_array);

    free(board->created_double_missing_connection_tile_array[LINE_SHAPE_IDX]);
    free(board->created_double_missing_connection_tile_array[BEND_SHAPE_IDX]);

    free(board);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------- Pre adding check function ------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// -------------- Helper functions and macros

/**
 * @note Macros meant only to be used in "can_piece_be_added_to_board" function
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

// Assuming the directions of missing connections are different, do their sum is a bend-shape or a line-shape
#define is_line_shape_computation()                                                                                                 \
    do                                                                                                                              \
    {                                                                                                                               \
        is_line_shape = (abs((current_tile->connection_direction_array[0]) - (existing_tile->connection_direction_array[0]))) == 2; \
    } while (0)

// helper function to check if a tile respect the obligatory tile matrix which is the data of level hints
// see can_piece_be_added_to_board
static bool is_tile_matching_level_hints(Tile *current_tile, Tile *obligatory_tile)
{
    static int connection_idx;

    if (obligatory_tile == UNDEFINED_TILE)
        return true; // Case where there's no obligatory data on this position

    if (current_tile->tile_type != obligatory_tile->tile_type)
        return false; // If their type is not matching, neither their connection directions

    if (obligatory_tile->tile_type == point)
        return true; // In this special case, we don't need to check for connection directions

    // Connection directions matching check
    for (connection_idx = 0; connection_idx < obligatory_tile->nb_of_connections; connection_idx++)
    {
        if (obligatory_tile->connection_direction_array[connection_idx] != current_tile->connection_direction_array[connection_idx])
            return false; // it is dangerous to have a fixed order check, but if I encoded all the connection direction datas correctly (by following always the same adding order (RIGHT,DOWN,LEFT,UP)), it shouldn't be an issue even with rotation_direction operation
    }
    return true;
}

// helper function to check if a normal tile connection directions fulfill the corresponding missing_connection tile ones
// see can_piece_be_added_to_board
static bool is_tile_matching_missing_connections(Tile *normal_tile, Tile *missing_connection_tile)
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

// -------------- Main function

// Function to check if a piece can be added to the board while blitting its live data cache which will be used to add it
//  A piece can be added to the board if all of the below checks pass :
//  To every normal tile of the blitted piece :
//  * tile is not outside the board
//  * tile is not superposed to existing normal tile on the board
//  * if it is superposed to an existing missing_connection_tile / double missing connection tile: does the connection of the normal tile fulfill the missing connection(s)
//  * if this tile emplacement is in the level hints (i.e. not UNDEFINED_TILE), check if the tile_type is the same (always) + connections are the same (only if the tile is not a point)
// To every missing connection tile of the blitted piece :
// * tile is not outside the board
// * if tile is superposed to an existing normal tile -> does the connection of the normal tile fulfill the missing connection
// * tile can be superposed to another existing missing connection tile to form a double missing connection tile, if and only if special pieces containing the corresponding double connexion has not been played
// (only line2 2 has a tile that can fulfill a double missing connection in a line and only T piece has tile that can fulfill a double missing connection in a bend)
// * triple missing connection can't be valid
//
// The function discard all computations as soon as it has been detected that the piece doesn't fit and returns an error code
// else returns 1 (true)
// Let the more likely error cases be check in first to make the whole thing faster
// (It doesn't matter if garbage / incomplete data is left in the piece cache, as only piece cache that had been through this function will be used in the rest of the program)
static int can_piece_be_added_to_board(Board *board, Side *side, Vector2_int base_pos, int rotation_state)
{

    static Tile *current_tile = NULL;
    static Tile *existing_tile = NULL;
    static Tile *obligatory_tile = NULL;
    static int i;
    static int connection_idx;
    static bool is_line_shape;

    // Missing connection tiles are checked in first, as there are usually less of them in game pieces
    // Less checks to be done to them compared to normal tiles
    // and they are more likely to be blitted out of bounds in the first place

    // ----------------------------------------------------------
    // ------ Missing connection tiles checks -------------------
    // ----------------------------------------------------------
    for (i = 0; i < side->nb_of_missing_connection_tiles; i++)
    {
        current_tile = (side->missing_connection_tile_array) + i;

        tile_absolute_pos_computation();

        // checks done to absolute postion of the tile
        if (!is_pos_inside_board(&(current_tile->absolute_pos)))
            return OUT_OF_BOUNDS;

        // connection directions are needed for all further checks
        tile_connection_directions_computation();

        existing_tile = board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j];

        if (existing_tile == UNDEFINED_TILE)
            continue; // case where the board is free at this position, there's no further checks

        if (existing_tile->tile_type != missing_connection)
        {
            // Case where a normal tile already exist at this position on the board
            // does it fulfill missing connections of current_tile ?
            if (!is_tile_matching_missing_connections(existing_tile, current_tile))
                return TILE_NOT_MATCHING_MISSING_CONNECTIONS;
        }
        else
        {
            // case where 2 missing connection tiles are about to be superposed, there's multiple cases to be considered

            // the existing tile could already be a double missing connection tile, a triple missing connection tile can't exist in vanilla game setup
            if (existing_tile->nb_of_connections >= 2)
                return TRIPLE_MISSING_CONNECTION_TILE;

            is_line_shape_computation();

            // A line-shape double missing connection tile can only exist if line2 2 piece has not been played yet
            if (is_line_shape && !(board->has_line2_2_been_added))
                continue;

            // A bend-shape double missing connection tile can only exist if T-piece has not been played yet
            // (we assume that if it's not a line-shape, it's necessary a bend-shape)
            if (!is_line_shape && !(board->has_T_piece_been_added))
                continue;

            // Else there can't be a double missing connection tile in vanilla game
            return INVALID_DOUBLE_MISSING_CONNECTION;
        }
    }

    // ----------------------------------------------
    // ------ Normal tiles checks -------------------
    // ----------------------------------------------
    for (i = 0; i < side->nb_of_tiles; i++)
    {
        current_tile = (side->tile_array) + i;

        tile_absolute_pos_computation();

        // checks done to absolute postion of the tile
        if (!is_pos_inside_board(&(current_tile->absolute_pos)))
            return OUT_OF_BOUNDS;

        // checks done to absolute position of the tile with extra information if there is already an existing tile at this position
        existing_tile = board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j];

        if (existing_tile == UNDEFINED_TILE)
        {
            // In this case, there's no further comparaison to existing tile as the tile in the board is free
            // but its connection directions still need to be computed
            tile_connection_directions_computation();
        }
        else
        {
            // Case where a tile already exist at this position on the board and superposition of two normal tiles is not allowed
            // we don't need to have computed connection directions to check this
            if (existing_tile->tile_type != missing_connection)
                return SUPERPOSED_TILES;

            // tile connection direction change computation needed for further checking
            tile_connection_directions_computation();

            if (!is_tile_matching_missing_connections(current_tile, existing_tile))
                return TILE_NOT_MATCHING_MISSING_CONNECTIONS;
        }

        // Check if the tile match level hints
        obligatory_tile = board->obligatory_tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j];

        if (!is_tile_matching_level_hints(current_tile, obligatory_tile))
            return TILE_NOT_MATCHING_LEVEL_HINTS;
    }

    return 1;
}

// --------------------

/**
 * @todo clarify this function when the search module is added
 */
// Function to only check if a position is already taken by a normal tile on the board
// used to skip multiple iterations of differents positions even before trying to add the piece to the board
// see
bool is_position_already_occupied(Board *board, Vector2_int base_pos)
{
    static Tile *tile;
    tile = board->tile_matrix[base_pos.i][base_pos.j];

    if (tile == UNDEFINED_TILE)
        return false;

    if (tile->tile_type == missing_connection)
        return false;

    return true;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------- adding and removing functions ------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// in similar sub functions we assume input validity
// otherwise it would not have been very safe, with risk of infinite loops, etc

static void push_missing_connection_tile_to_array(Board *board, Tile *tile)
{
    board->missing_connection_tile_array[board->nb_of_missing_connection_tiles] = tile;
    board->nb_of_missing_connection_tiles++;
}

static void remove_missing_connection_tile_from_array(Board *board, Tile *tile)
{
    //@todo let's add a better data structure to record those things and have ore efficient operations ?
    // function not tested yet
    static Tile *current_tile = NULL;
    static int idx;
    idx = -1;
    do
    {
        idx++;
        current_tile = board->missing_connection_tile_array[idx];
    } while (current_tile != tile);

    // board->missing_connection_tile_array[idx] = UNDEFINED_TILE;
    idx++;
    while (idx < board->nb_of_missing_connection_tiles)
    {
        board->missing_connection_tile_array[idx - 1] = board->missing_connection_tile_array[idx];
        idx++;
    }
    board->missing_connection_tile_array[idx - 1] = UNDEFINED_TILE;
    board->nb_of_missing_connection_tiles--;
}

static void pop_missing_connection_tile_from_array(Board *board)
{
    board->nb_of_missing_connection_tiles--;
    board->missing_connection_tile_array[board->nb_of_missing_connection_tiles] = UNDEFINED_TILE;
}

// Function to blit a piece to the board
// Return false if the piece doesn't fit at all (by checking "can_piece_be_added_to_board")
// Return true if the piece has been successfully added
bool add_piece_to_board(Board *board, int piece_idx, int side_idx, Vector2_int base_pos, int rotation_state)
{

    static Piece *piece = NULL;
    static Side *side = NULL;
    static Tile *current_tile = NULL;
    static Tile *existing_tile = NULL;
    static int tile_idx = 0;
    static bool is_line_shape = false;
    static int shape_idx = 0;
    static Direction direction;
    static int temp_connection_idx;

    piece = board->piece_array + piece_idx;
    side = piece->side_array + side_idx;

    // check if the piece can even fit in the board while loading it by the same occasion
    if (can_piece_be_added_to_board(board, side, base_pos, rotation_state) != true) // to confirm only the case where 1 is returned
        return false;

    piece->current_side_idx = side_idx;

    // adding normal tile data to the board
    for (tile_idx = 0; tile_idx < side->nb_of_tiles; tile_idx++)
    {
        current_tile = side->tile_array + tile_idx;
        existing_tile = board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j];
        if (existing_tile != UNDEFINED_TILE && existing_tile->tile_type == missing_connection)
            remove_missing_connection_tile_from_array(board, existing_tile);

        board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j] = current_tile; // pointer copy
    }

    // adding missing connection tile data to the board
    for (tile_idx = 0; tile_idx < side->nb_of_missing_connection_tiles; tile_idx++)
    {
        current_tile = side->missing_connection_tile_array + tile_idx;
        existing_tile = board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j];

        if (existing_tile == UNDEFINED_TILE)
        {
            board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j] = current_tile;
            push_missing_connection_tile_to_array(board, current_tile);
        }
        else
        {
            // double missing connection case
            // 1) find out either line double connection shape, or bend shape
            is_line_shape_computation();
            // 2) fill informations of the double connection tile in an independent new tile object
            shape_idx = is_line_shape ? LINE_SHAPE_IDX : BEND_SHAPE_IDX;
            board->created_double_missing_connection_tile_array[shape_idx]->tile_type = missing_connection;
            board->created_double_missing_connection_tile_array[shape_idx]->absolute_pos = existing_tile->absolute_pos;
            board->created_double_missing_connection_tile_array[shape_idx]->nb_of_connections = 2;

            // /!\ for other methods to work, the connection directions must be put in a precise order
            temp_connection_idx = 0;
            for (direction = RIGHT; direction < NB_OF_DIRECTIONS; direction++)
            {
                if (direction == current_tile->connection_direction_array[0] || direction == existing_tile->connection_direction_array[0])
                {
                    board->created_double_missing_connection_tile_array[shape_idx]->connection_direction_array[temp_connection_idx] = direction;
                    temp_connection_idx++;
                }
            }
            /**
             * @todo maybe there are other fields to fill for this to work
             **/

            // 3) record wth pointer
            board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j] = board->created_double_missing_connection_tile_array[shape_idx];
            board->double_missing_connection_tile_array[shape_idx] = board->created_double_missing_connection_tile_array[shape_idx];
        }
    }

    // check if the piece added is a special piece that we care for double missing connection tiles
    switch (piece_idx)
    {
    case LINE2_2:
        board->has_line2_2_been_added = true;
        break;
    case T_PIECE:
        board->has_T_piece_been_added = true;
    default:
        break;
    }
    board->added_piece_idx_array[board->nb_of_added_pieces] = piece_idx;
    board->nb_of_added_pieces++;

    return true;
}

// Function to undo the last "add_piece_to_board" operation
void undo_last_piece_adding()
{
    // la question, c'est "est-ce que je le fais inplace ou plutôt de façon dumb ?"

    // la méthode inplace, ça serait de trouver une giga logique pour record tout ce qu'on a ajouté et remettre la board en place

    // ou alors faire un nouvel objet "prec_board" dont on charge et décharge la mémoire bit par bit
    // genre une board temporaire, on doit copier la board actuelle dans la prec board au début de l'opération d'adding (mais après le check que l'adding passe bien)

    // go faire la 2ème méthode, mais en revoyant les vidéos pour bien copier des structs
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------- Post adding check functions ------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
