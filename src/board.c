/**
 * @file board.c
 *
 * We can think of pieces, like a fancy way to blit independent tiles to the board
 *
 * So a board is a variable to represent the current state of the game.
 * In this file, we can add and remove pieces to and from the board.
 * see test_display.c to see it in action
 *
 * It will be used by the main search algorithm, that will automatically add and remove pieces from a board according to what we are trying to solve.
 */

#include <local/board.h>

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------- Board constructor / destructor ------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Board *init_board()
{
    Board *board = malloc(sizeof(Board));

    // 1) Basic data init
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

    // 4) set stop end of stacks in tile matrix (implemented like linked lists)
    int piece_idx;
    Piece *piece;
    int side_idx;
    Side *side;
    int tile_idx;

    for (piece_idx = 0; piece_idx < NB_OF_PIECES; piece_idx++)
    {
        piece = (board->piece_array) + piece_idx;

        for (side_idx = 0; side_idx < piece->nb_of_sides; side_idx++)
        {

            side = (piece->side_array) + side_idx;

            for (tile_idx = 0; tile_idx < side->nb_of_tiles; tile_idx++)
                side->tile_array[tile_idx].next = UNDEFINED_TILE;

            for (tile_idx = 0; tile_idx < side->nb_of_missing_connection_tiles; tile_idx++)
                side->missing_connection_tile_array[tile_idx].next = UNDEFINED_TILE;
        }
    }

    // 5) Load level hints (add obligatory pieces and load obligatory tile matrix)
    // @todo

    return board;
}

void free_board(Board *board)
{
    free(board->piece_array);
    free(board);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------- Pre adding check function ------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// -------------- Helper functions and macros ----------------------------------------------------------------------------------------------

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
static bool is_tile_matching_missing_connections(Tile *normal_tile, Tile *missing_connection_tile_stack)
{

    // normal_tile is supposedly not a stack, just a single tile
    // missing_connection_tile_stack could be a single tile or a tile stack (but there are guaranteed only missing_connection tiles in this stack)
    // regarding both use cases of this function in "can_piece_be_added_to_board"

    static int connection_idx;
    static Direction direction_searched_for;
    static bool direction_found;

    static Tile *temp_tile = NULL;

    temp_tile = missing_connection_tile_stack;

    while (temp_tile != UNDEFINED_TILE)
    {
        direction_searched_for = temp_tile->connection_direction_array[0];
        direction_found = false;
        for (connection_idx = 0; connection_idx < normal_tile->nb_of_connections; connection_idx++)
        {
            if (normal_tile->connection_direction_array[connection_idx] == direction_searched_for)
            {
                direction_found = true;
                break;
            }
        }
        // we must have direction_found == true at each iteration of while loop for the whole function to return true
        if (!direction_found)
            return false;

        temp_tile = temp_tile->next;
    }

    return true;
}

// Return a pointer to a normal tile in the input stack (linked list) of tiles
// Return UNDEFINED_TILE if not found
static Tile *extract_normal_tile_from_stack(Tile *tile_stack)
{
    static Tile *temp_tile = NULL;
    temp_tile = tile_stack;
    while (temp_tile != UNDEFINED_TILE)
    {
        if (temp_tile->tile_type != missing_connection)
            return temp_tile;

        temp_tile = temp_tile->next;
    }
    return UNDEFINED_TILE;
}

// public tool to interact with the board
// function that return a tile pointer on the normal tile at base_pos (i,j) on the board
// if there is any, and return UNDEFINED_TILE if not found
Tile *extract_normal_tile_at_pos(Board *board, Vector2_int *base_pos)
{
    return extract_normal_tile_from_stack(board->tile_matrix[base_pos->i][base_pos->j]);
}

// -------------- Main function --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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
    static Tile *existing_tile_stack = NULL;
    static Tile *existing_normal_tile = NULL;
    static Tile *obligatory_tile = NULL;
    static int tile_idx;
    static int connection_idx;
    static bool is_line_shape;

    // Missing connection tiles are checked in first, as there are usually less of them in game pieces
    // Less checks to be done to them compared to normal tiles
    // and they are more likely to be blitted out of bounds in the first place

    // ----------------------------------------------------------
    // ------ Missing connection tiles checks -------------------
    // ----------------------------------------------------------
    for (tile_idx = 0; tile_idx < side->nb_of_missing_connection_tiles; tile_idx++)
    {
        current_tile = (side->missing_connection_tile_array) + tile_idx;

        tile_absolute_pos_computation(); // see piece.h

        // checks done to absolute postion of the tile
        if (!is_pos_inside_board(&(current_tile->absolute_pos)))
            return OUT_OF_BOUNDS;

        // connection directions are needed for all further checks
        tile_connection_directions_computation(); // see piece.h

        existing_tile_stack = board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j];

        if (existing_tile_stack == UNDEFINED_TILE)
            continue; // case where the board is free at this position, there's no further checks

        // is there already a normal tile in the existing tile ?
        existing_normal_tile = extract_normal_tile_from_stack(existing_tile_stack);
        if (existing_normal_tile != UNDEFINED_TILE)
        {

            // Case where a normal tile already exist at this position on the board
            // does it fulfill missing connections of current_tile ?
            if (!is_tile_matching_missing_connections(existing_normal_tile, current_tile))
                return TILE_NOT_MATCHING_MISSING_CONNECTIONS;
        }
        else
        {
            // case where 2 missing connection tiles are about to be superposed, there's multiple cases to be considered

            // the existing tile could already be a double missing connection tile, a triple missing connection tile can't exist in vanilla game setup
            if (existing_tile_stack->next != UNDEFINED_TILE)
                return TRIPLE_MISSING_CONNECTION_TILE;

            // Assuming the directions of missing connections are different, do their sum is a bend-shape or a line-shape
            // only 2 case where the shape formed by the 2 directions can be a line : (RIGHT:0,LEFT:2) (means horizontal line) and (DOWN:1,UP:3) (means vertical line)
            // otherwise it's a bend shape
            is_line_shape = (abs((current_tile->connection_direction_array[0]) - (existing_tile_stack->connection_direction_array[0]))) == 2;

            // A line-shape double missing connection tile can only exist if line2 2 piece has not been played yet
            if (is_line_shape && !(board->has_line2_2_been_added))
                continue;

            // A bend-shape double missing connection tile can only exist if T-piece has not been played yet
            if (!is_line_shape && !(board->has_T_piece_been_added))
                continue;

            // Else there can't be a double missing connection tile in vanilla game
            return INVALID_DOUBLE_MISSING_CONNECTION;
        }
    }

    // ----------------------------------------------
    // ------ Normal tiles checks -------------------
    // ----------------------------------------------
    for (tile_idx = 0; tile_idx < side->nb_of_tiles; tile_idx++)
    {
        current_tile = (side->tile_array) + tile_idx;

        tile_absolute_pos_computation();

        // checks done to absolute postion of the tile
        if (!is_pos_inside_board(&(current_tile->absolute_pos)))
            return OUT_OF_BOUNDS;

        // checks done to absolute position of the tile with extra information if there is already an existing tile at this position
        existing_tile_stack = board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j];

        if (existing_tile_stack == UNDEFINED_TILE)
        {
            // In this case, there's no further comparaison to existing tile as the tile in the board is free
            // but its connection directions still need to be computed
            tile_connection_directions_computation();
        }
        else
        {
            // Case where a tile already exist at this position on the board and superposition of two normal tiles is not allowed
            // we don't need to have computed connection directions to check this
            if (extract_normal_tile_from_stack(existing_tile_stack) != UNDEFINED_TILE)
                return SUPERPOSED_TILES;

            // tile connection direction change computation needed for further checking
            tile_connection_directions_computation();

            if (!is_tile_matching_missing_connections(current_tile, existing_tile_stack))
                return TILE_NOT_MATCHING_MISSING_CONNECTIONS;
        }

        // Check if the tile match level hints
        obligatory_tile = board->obligatory_tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j];

        if (!is_tile_matching_level_hints(current_tile, obligatory_tile))
            return TILE_NOT_MATCHING_LEVEL_HINTS;
    }

    return true;
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
    static Tile *tile_stack;
    tile_stack = board->tile_matrix[base_pos.i][base_pos.j];

    if (extract_normal_tile_from_stack(tile_stack) == UNDEFINED_TILE)
        return false;

    return true;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------- adding and removing functions ------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Function to blit a piece to the board
// Return error code if the piece doesn't fit at all (by checking "can_piece_be_added_to_board")
// In this case, it doesn't do anything
// The error code returned is the same as "can_piece_be_added_to_board"
// Return true (1) if the piece has been successfully added
int add_piece_to_board(Board *board, int piece_idx, int side_idx, Vector2_int base_pos, int rotation_state)
{
    static int error_code;

    static Piece *piece = NULL;
    static Side *side = NULL;
    static Tile *current_tile = NULL;
    static Tile *existing_tile_stack = NULL;
    static int tile_idx = 0;

    piece = (board->piece_array) + piece_idx;
    side = (piece->side_array) + side_idx;

    // check if the piece can even fit in the board while loading it by the same occasion
    error_code = can_piece_be_added_to_board(board, side, base_pos, rotation_state);
    if (error_code != true) // to confirm only the case where 1 is returned
        return error_code;

    // adding normal tile data to the board
    for (tile_idx = 0; tile_idx < side->nb_of_tiles; tile_idx++)
    {
        current_tile = side->tile_array + tile_idx;
        existing_tile_stack = board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j];
        // we don't even need to check existing tile, to see if the superposition is allowed, as it has already been done in "can_piece_be_added_to_board"
        // we just do the superposition
        current_tile->next = existing_tile_stack; // works even if existing_tile_stack == UNDEFINED_TILE
        board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j] = current_tile;
    }

    // adding missing connection tile data to the board (same exact remarks as in normal tiles case)
    for (tile_idx = 0; tile_idx < side->nb_of_missing_connection_tiles; tile_idx++)
    {

        current_tile = side->missing_connection_tile_array + tile_idx;
        existing_tile_stack = board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j];

        current_tile->next = existing_tile_stack;
        board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j] = current_tile;
    }

    // Record of current blit inputs for the later modular blit functions
    piece->current_side_idx = side_idx;
    piece->current_base_pos.i = base_pos.i;
    piece->current_base_pos.j = base_pos.j;
    piece->current_rotation_state = rotation_state;

    // check if the piece added is a special piece that we care for double missing connection tiles
    switch (piece_idx)
    {
    case LINE2_2:
        board->has_line2_2_been_added = true;
        break;
    case T_PIECE:
        board->has_T_piece_been_added = true;
        break;
    default:
        break;
    }

    // Record other board attributes
    board->added_piece_idx_array[board->nb_of_added_pieces] = piece_idx;
    board->nb_of_added_pieces++;

    return true;
}

// Function to undo the last "add_piece_to_board" operation
void undo_last_piece_adding(Board *board)
{
    static int piece_idx;
    static Piece *piece = NULL;
    static Side *side = NULL;
    static Tile *current_tile = NULL;
    static int tile_idx = 0;

    // grab the last piece_idx added and "remove it" from the stack
    board->nb_of_added_pieces--;
    piece_idx = board->added_piece_idx_array[board->nb_of_added_pieces];

    piece = (board->piece_array) + piece_idx;
    side = (piece->side_array) + piece->current_side_idx;

    // check if the piece added is a special piece that we care for double missing connection tiles
    switch (piece_idx)
    {
    case LINE2_2:
        board->has_line2_2_been_added = false;
        break;
    case T_PIECE:
        board->has_T_piece_been_added = false;
        break;
    default:
        break;
    }

    // undo the superposition of normal tiles and missing_connection tiles of the piece (which is still at the same location)
    for (tile_idx = 0; tile_idx < side->nb_of_tiles; tile_idx++)
    {
        current_tile = (side->tile_array) + tile_idx;
        board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j] = current_tile->next;
        current_tile->next = UNDEFINED_TILE;
    }

    for (tile_idx = 0; tile_idx < side->nb_of_missing_connection_tiles; tile_idx++)
    {
        current_tile = (side->missing_connection_tile_array) + tile_idx;
        board->tile_matrix[current_tile->absolute_pos.i][current_tile->absolute_pos.j] = current_tile->next;
        current_tile->next = UNDEFINED_TILE;
    }
}