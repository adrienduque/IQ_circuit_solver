/**
 * @file check_board.c
 *
 * File where we will have a succession checking methods to determine if the current state of a board is worthy to be continued on
 * Or if we know that this state doesn't have any change of leading to a complete board
 */

/**
 * @todo new check idea in addition to those in python project :
 * if the double missing connection still exist after its corresponding piece has been played
 * we know for a fact that no other piece can fill it and thus, the board is discarded
 * -> let's integrate it in a test where we have to scan the board 1 tile per 1 tile, and we will detect double missing connections
 */

#include <local/check_board.h>
#include <stdio.h> // @todo temp for debugging checking methods

static bool is_tile_pos_isolated(Board *board, Vector2_int pos)
{
    static Direction dir;
    static Vector2_int temp_pos;
    // it must have at least an empty neighbour (empty in terms of normal tiles only: missing connection tiles doesn't count as "filled")
    for (dir = RIGHT; dir < NB_OF_DIRECTIONS; dir++)
    {
        temp_pos = pos;
        increment_pos_in_direction(&temp_pos, dir);
        if (!is_pos_inside_board(&temp_pos))
            continue; // an increment might lead to out of bounds

        // is there another empty tile at this neighbour location ?
        if (extract_normal_tile_at_pos(board, &temp_pos) == UNDEFINED_TILE)
            return false; // case where the answer is yes
    }

    return true;
}
// Function to check if adding the piece to the board didn't let an empty tile completely isolated
// Because we know that it can't be filled by any piece and all tiles must be filled to have a complete board
// We only have to check tiles around the piece (which are called "border tiles")
// Returns bool, true if everything is fine
static bool check_isolated_tiles_around_piece(Board *board, Piece *piece)
{
    static int i;
    static Vector2_int pos;

    update_piece_border_tiles(piece);

    for (i = 0; i < piece->nb_of_border_tiles; i++)
    {
        pos = piece->border_tile_absolute_pos_array[i];
        if (!is_pos_valid(&pos))
            continue; // we know already if a border tile is within board boundary or not, we only check if not out of bounds

        if (extract_normal_tile_at_pos(board, &pos) != UNDEFINED_TILE)
            continue; // case where the border tile is already filled with a normal tile, they are not concerned by this check, only empty border tiles

        if (is_tile_pos_isolated(board, pos))
            return false; // if only 1 of empty border tiles is isolated, the whole check fail
    }

    return true;
}

// ---------------------------------------------------------------------------------------------------------------------------

// Function to follow a connection path from a missing connection starting point
// Stop following the path if it reach a point tile, an end of path (incomplete path), or if it detected that it followed a loop path
// Returns the board tile stack pointer, of the location where it stopped following the path
static Tile *follow_path(Board *board, Tile *missing_connection_tile)
{
    // warning : the input missing connnection might already been filled on the board but it doesn't matter
    static Tile *current_tile_stack = UNDEFINED_TILE;
    static Tile *normal_tile = UNDEFINED_TILE;
    static Vector2_int current_pos, start_pos;
    static Direction next_direction, discarded_direction;
    static int connection_idx;

    start_pos = missing_connection_tile->absolute_pos;

    next_direction = missing_connection_tile->connection_direction_array[0];

    current_pos = missing_connection_tile->absolute_pos;

    while (next_direction != -1)
    {
        increment_pos_in_direction(&current_pos, next_direction);
        current_tile_stack = board->tile_matrix[current_pos.i][current_pos.j];

        if (are_pos_equal(&start_pos, &current_pos))
            // case where : we followed a loop path
            // or what will become a loop, if we are currently on a double missing connection tile
            // in both cases, stop following the path
            break;

        // is there a normal tile at this location ?
        normal_tile = extract_normal_tile_from_stack(current_tile_stack);

        if (normal_tile == UNDEFINED_TILE)
            // answer : no
            // case where the path ends, the current_pos is on a missing connection tile (or double missing), that is not filled
            // stop following the path
            break;
        // answer : yes
        // general case where the next tile in the path is a normal tile
        // we have to follow its connection directions without going backwards
        discarded_direction = reverse_direction(next_direction);
        next_direction = -1; // if we don't found a new direction to go, we stop following the path, as we are on a point tile
        for (connection_idx = 0; connection_idx < normal_tile->nb_of_connections; connection_idx++)
        {
            // pick the first next direction that is not the discarded direction
            if (normal_tile->connection_direction_array[connection_idx] == discarded_direction)
                continue;

            next_direction = normal_tile->connection_direction_array[connection_idx];
            break;
        }
    }

    return current_tile_stack;
}

// Function to make sure that adding the piece to the board didn't create loop connection path
// As they are not allowed in the game rules
// Therefore, a board that contains a loop is not valid
static bool check_no_loops(Board *board, Piece *piece)
{
    // There are some rare cases where a future loop will not be identified by this algorithm
    // Where with the current played pieces, there is an incomplete loop path (we know it's not ok, because the only possibility to complete the path is to complete a loop)
    // If the last piece added to this incomplete loop path is not directly in contact with the whole in the loop
    // or if it is in direct contact, its not the right missing connection choosen in "susceptible_loop_generator_missing_connection_tile_idx_array", the missing connection where is the whole is ignored in piece_data.c

    // at least it detects complete loops 100% of the time

    static Side *side;
    static int tile_idx;
    static Tile *tile;
    static Tile *result_tile_stack;

    side = (piece->side_array) + (piece->current_side_idx);

    // follow the paths starting from each susceptible missing connection tile of the played piece
    // if the starting and ending point of the same path, are at the same position on the board, it's a loop
    for (tile_idx = 0; tile_idx < side->nb_of_susceptible_loop_generator_tiles; tile_idx++)
    {
        tile = (side->missing_connection_tile_array) + (side->susceptible_loop_generator_missing_connection_tile_idx_array[tile_idx]);
        result_tile_stack = follow_path(board, tile);

        if (are_pos_equal(&(tile->absolute_pos), &(result_tile_stack->absolute_pos)))
            // this is a loop
            return false;
    }

    return true;
}

// ---------------------------------------------------------------------------------------------------------------------------

// Function to run all checks that have to be done after a piece was added
// To see if the board is worth continuing or not
// As soon as one of the check don't pass, function discard all other computation and returns
// Let the more likely and easy-to-compute checks be in first to cut down more computation
// Returns int error_code based on the check that didn't pass else 1
int run_all_checks(Board *board)
{
    /**
     * @todo peut-être réarranger les checks, je les construits dans l'ordre du plus simple au plus dur
     * mais c'est pas forcément l'ordre opti d'exécution
     */
    static Piece *last_added_piece = NULL;

    last_added_piece = (board->piece_array) + board->added_piece_idx_array[board->nb_of_added_pieces - 1];

    if (!check_isolated_tiles_around_piece(board, last_added_piece))
        return ISOLATED_EMPTY_TILE;

    if (!check_no_loops(board, last_added_piece))
        return LOOP_PATH;

    return 1;
}