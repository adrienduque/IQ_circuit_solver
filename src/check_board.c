/**
 * @file check_board.c
 *
 * File where we will have a succession checking methods to determine if the current state of a board is worthy to be continued on
 * Or if we know that this state doesn't have any change of leading to a complete board
 */

/**
 * @todo when all the checks are implemented, observe a run of the algorithm very slowly and see if there are more ideas of checks to add
 * that come to mind
 */

#include <local/check_board.h>
#include <local/astar.h>
#include <stdio.h> // @todo temp for debugging checking methods
// all functions features are tested manually through printfs and playing with it in test_display.exe

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// -------------- Helper functions of "check_isoleted_tiles_around_piece" ---------------------------------------

static bool is_tile_pos_isolated(Board *board, const Vector2_int *pos)
{
    static Direction dir;
    static Vector2_int temp_pos;
    // it must have at least an empty neighbour (empty in terms of normal tiles only: missing connection tiles doesn't count as "filled" here)
    for (dir = RIGHT; dir < NB_OF_DIRECTIONS; dir++)
    {
        temp_pos.i = pos->i;
        temp_pos.j = pos->j;
        increment_pos_in_direction(&temp_pos, dir);
        if (!is_pos_inside_board(&temp_pos))
            continue; // an increment might lead to out of bounds

        // is there another empty tile at this neighbour location ?
        if (extract_normal_tile_at_pos(board, &temp_pos) == UNDEFINED_TILE)
            return false; // case where the answer is yes
    }

    return true;
}

// -------------- Main function ---------------------------------------------------------------------------------

// Function to check if adding the piece to the board didn't let an empty tile completely isolated
// Because we know that it can't be filled by any piece and all tiles must be filled to have a complete board
// We only have to check tiles around the piece (which are called "border tiles")
// Returns bool, true if everything is fine
static bool check_isolated_tiles_around_piece(Board *board, Piece *piece)
{
    static int i;
    static Vector2_int *pos;

    update_piece_border_tiles(piece);

    for (i = 0; i < piece->nb_of_border_tiles; i++)
    {
        pos = (piece->border_tile_absolute_pos_array) + i;
        if (!is_pos_valid(pos))
            continue; // we know already if a border tile is within board boundary or not, we only check if not out of bounds

        if (extract_normal_tile_at_pos(board, pos) != UNDEFINED_TILE)
            continue; // case where the border tile is already filled with a normal tile, they are not concerned by this check, only empty border tiles

        if (is_tile_pos_isolated(board, pos))
            return false; // if only 1 of empty border tiles is isolated, the whole check fail
    }

    return true;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// -------------- Helper function of "check_no_loops" ---------------------------------------

// (The one below also help the "check_no_dead_ends" method)

// Function to follow a connection path from a missing connection starting point
// Stop following the path if it reaches a point tile, an end of path (incomplete path), or if it detected that it followed a loop path
// Returns the board tile stack pointer, of the location where it stopped following the path
static Tile *follow_path(Board *board, Tile *missing_connection_tile)
{
    // warning : the input missing connnection might already been filled on the board but it doesn't matter
    static Tile *current_tile_stack = UNDEFINED_TILE;
    static Tile *normal_tile = UNDEFINED_TILE;
    static Vector2_int current_pos, start_pos;
    static Direction next_direction, discarded_direction;
    static int connection_idx;

    current_tile_stack = UNDEFINED_TILE;
    start_pos = missing_connection_tile->absolute_pos;

    next_direction = missing_connection_tile->connection_direction_array[0];

    current_pos = missing_connection_tile->absolute_pos;

    while (true)
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
        next_direction = -1;
        for (connection_idx = 0; connection_idx < normal_tile->nb_of_connections; connection_idx++)
        {
            // pick the first next direction that is not the discarded direction
            if (normal_tile->connection_direction_array[connection_idx] == discarded_direction)
                continue;

            next_direction = normal_tile->connection_direction_array[connection_idx];
            break;
        }

        if (next_direction == -1)
            break; // if we don't found a new direction to go, we stop following the path, as we are on a point tile
    }

    return current_tile_stack;
}

// -------------- Main function ---------------------------------------------------------------------------------

// Function to make sure that adding the piece to the board didn't create loop connection path
// As they are not allowed in the game rules
// Therefore, a board that contains a loop is not valid
static bool check_no_loops(Board *board, Piece *piece)
{
    // There are some rare cases where a future loop will not be identified by this algorithm
    // Where with the current played pieces, there is an incomplete loop path (1 tile hole in the path) (we know it's not ok, because the only possibility to complete the path is to complete a loop)
    // If the last piece added to this incomplete loop path is not directly in contact with the hole in the loop
    // or if it is in direct contact, its not the right missing connection choosen in "susceptible_loop_generator_missing_connection_tile_idx_array" (see piece_data.h), the missing connection where is the hole is ignored

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

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// -------------- Helper functions of "check_no_dead_ends" -----------------------------------------------------------

// Function to count the number of missing connection tiles in the tile stack
// (stack implemented as a linked list, see piece_data.h > Tile struct)
static int get_number_of_missing_connection_in_stack(Tile *tile_stack)
{
    static int nb;
    static Tile *temp_tile = NULL;

    nb = 0;
    temp_tile = tile_stack;

    while (temp_tile != UNDEFINED_TILE)
    {
        if (temp_tile->tile_type == missing_connection)
            nb++;

        temp_tile = temp_tile->next;
    }
    return nb;
}

// Function to get the nearest target tile from the starting tile
// also discard not_allowed_target_tile if not UNDEFINED_TILE (alias for NULL)
// returns an int index of missing_connection_to_check_array (which is the list of potential target tiles)
// returns -1 if there is no nearest valid target tile
static int get_nearest_target_tile_idx(Tile *start_tile, Tile *missing_connection_to_check_array[NB_OF_PIECES * MAX_NB_OF_MISSING_CONNECTION_PER_SIDE], int nb_of_missing_connections_to_check, Tile *not_allowed_target_tile)
{
    static int min_dist, min_idx, idx, dist;
    static Tile *tile;

    min_dist = INT_MAX;
    min_idx = -1;

    for (idx = 0; idx < nb_of_missing_connections_to_check; idx++)
    {
        tile = missing_connection_to_check_array[idx];
        if (are_pos_equal(&(start_tile->absolute_pos), &(tile->absolute_pos)))
            continue;
        if (not_allowed_target_tile != UNDEFINED_TILE && are_pos_equal(&(not_allowed_target_tile->absolute_pos), &(tile->absolute_pos)))
            continue;

        dist = manhattan_dist(&(start_tile->absolute_pos), &(tile->absolute_pos));

        if (dist < min_dist)
        {
            min_idx = idx;
            min_dist = dist;
        }
    }

    return min_idx;
}

// -------------- Main function ---------------------------------------------------------------------------------

// Function to check if the current open missing connections on the board can still be linked by a future path between them
// If not, this is obviously bad, and the board is discarded
// How do I check this ?
// 1) First off : pick the board tiles that are concerned by this check
// We want all open missing connections ("open" meaning that, they aren't filled yet by other piece normal tiles on the board)
// We don't want double missing connections either (as the path linking them is necessary a single tile, it's like a trivial case)
// We also want to include level obligatory point tiles, if they are still open
// Result : a list of tile position to check
// 2) For each tile to check : run a pathfinding algorithm starting from this tile , and see if there's at least one valid path remaining to another tile position to check
// (if an open missing connection tile is linked by an actual path to the starting tile, this tile is discarded from the valid targets list, for this particular pathfinding) (mostly to avoid pieces that find a valid path to themselve)
// we target the nearest other tile from the list (other = different from the starting tile), but all other tiles from the list can be valid ending to the pathfinding algorithm
// as we don't predict paths, the actual nearest target might not be the one the algorithm ends up on, but is a good hint
// if the pathfinding algorithm find a path, the ending tile of the path is recorded as already checked
// if the pathfinding algorithm can't find at least one valid path for each tile to check, it means that there's a dead end and the function returns false
// else returns true
static bool check_no_dead_ends(Board *board)
{
    // temp variables
    static int piece_idx, tile_idx, i, j;
    static Piece *piece;
    static Side *side;
    static Tile *tile;
    static Tile *board_tile_stack;
    static Tile *start_tile, *not_allowed_target_tile, *nearest_target_tile, *end_tile;
    static int nearest_target_tile_idx;

    // starting and ending points of the pathfinding algorithm
    static Tile *missing_connection_to_check_array[NB_OF_PIECES * MAX_NB_OF_MISSING_CONNECTION_PER_SIDE + MAX_NB_OF_OPEN_POINT_TILES_PER_LEVEL];
    static int nb_of_missing_connections_to_check;
    static bool has_already_been_check_matrix[BOARD_WIDTH][BOARD_HEIGHT];
    static SimpleTileType temp_removed_representation_infos[2];
    static SimpleTileType board_representation_matrix[BOARD_WIDTH][BOARD_HEIGHT]; // see astar.h

    nb_of_missing_connections_to_check = 0;

    // initialize board_representation_matrix
    for (i = 0; i < BOARD_WIDTH; i++)
    {
        for (j = 0; j < BOARD_HEIGHT; j++)
            board_representation_matrix[i][j] = no_info;
    }

    // 1) Picking the starting tiles to check

    // append the open points of the level hints
    //(before the actual missing connection tiles to start by them in 2))
    // (because the pathfinding starting from these tiles is more likely to end up on a missing connection tile, thus mark it as already checked, and letting us skip iterations)
    for (tile_idx = 0; tile_idx < board->nb_of_open_obligatory_point_tiles; tile_idx++)
    {
        tile = board->open_obligatory_point_tile_array[tile_idx];
        board_tile_stack = board->tile_matrix[tile->absolute_pos.i][tile->absolute_pos.j];

        // mini different check added : double missing connections are just not allowed on a open tile point (there's no piece that has a point tile with 2 connections)
        if (get_number_of_missing_connection_in_stack(board_tile_stack) == 2)
            return false;

        // is the point already filled ? (even if it's already filled with a missing connection, it's already taken into account, so ignore it)
        if (board_tile_stack != UNDEFINED_TILE)
            //  yes so skip it
            continue;

        has_already_been_check_matrix[tile->absolute_pos.i][tile->absolute_pos.j] = false;
        board_representation_matrix[tile->absolute_pos.i][tile->absolute_pos.j] = target;
        missing_connection_to_check_array[nb_of_missing_connections_to_check] = tile;
        nb_of_missing_connections_to_check++;
    }

    // append the open missing connection tiles of the already played pieces
    for (piece_idx = 0; piece_idx < board->nb_of_added_pieces; piece_idx++)
    {
        piece = (board->piece_array) + board->added_piece_idx_array[piece_idx];
        side = (piece->side_array) + (piece->current_side_idx);

        for (tile_idx = 0; tile_idx < side->nb_of_missing_connection_tiles; tile_idx++)
        {
            tile = (side->missing_connection_tile_array) + tile_idx;
            board_tile_stack = board->tile_matrix[tile->absolute_pos.i][tile->absolute_pos.j];

            // is the missing connection already filled ?
            if (extract_normal_tile_from_stack(board_tile_stack) != UNDEFINED_TILE)
                // yes so skip it
                continue;

            // also ignore double missing connection tiles
            if (get_number_of_missing_connection_in_stack(board_tile_stack) == 2)
                continue;

            has_already_been_check_matrix[tile->absolute_pos.i][tile->absolute_pos.j] = false;
            board_representation_matrix[tile->absolute_pos.i][tile->absolute_pos.j] = target;
            missing_connection_to_check_array[nb_of_missing_connections_to_check] = tile;
            nb_of_missing_connections_to_check++;
        }
    }

    // 2)  pathfinding algorithm for each missing connection tile to check

    for (tile_idx = 0; tile_idx < nb_of_missing_connections_to_check; tile_idx++)
    {
        start_tile = missing_connection_to_check_array[tile_idx];

        // check if we can skip this starting_tile
        if (has_already_been_check_matrix[start_tile->absolute_pos.i][start_tile->absolute_pos.j])
            continue;

        // compute the tile which is linked by an actual path to the starting tile (if there is one)
        not_allowed_target_tile = UNDEFINED_TILE;
        if (start_tile->tile_type != point)
            // can't follow a connection path if the start_tile is a open point of the level
            not_allowed_target_tile = follow_path(board, start_tile);

        // Get the nearest target tile from the starting tile
        // also discard not_allowed_target_tile
        nearest_target_tile_idx = get_nearest_target_tile_idx(start_tile, missing_connection_to_check_array, nb_of_missing_connections_to_check, not_allowed_target_tile);
        if (nearest_target_tile_idx == -1)
            // there's not a single valid target for this start_tile
            return false;
        nearest_target_tile = missing_connection_to_check_array[nearest_target_tile_idx];

        // we don't want starting tile and not_allowed_target_tile as valid ending targets in the pathfinding algorithm
        // temporary remove them from board representation
        // They will be restored for the next iterations
        if (not_allowed_target_tile != NULL)
        {
            temp_removed_representation_infos[0] = board_representation_matrix[not_allowed_target_tile->absolute_pos.i][not_allowed_target_tile->absolute_pos.j];
            board_representation_matrix[not_allowed_target_tile->absolute_pos.i][not_allowed_target_tile->absolute_pos.j] = no_info;
        }
        temp_removed_representation_infos[1] = board_representation_matrix[start_tile->absolute_pos.i][start_tile->absolute_pos.j];
        board_representation_matrix[start_tile->absolute_pos.i][start_tile->absolute_pos.j] = no_info;

        // actual pathfinding that returns the tile that it ends up on, if it found a path to it, see astar.c
        end_tile = find_a_path(board, &(start_tile->absolute_pos), &(nearest_target_tile->absolute_pos), board_representation_matrix);

        // main concern check
        if (end_tile == UNDEFINED_TILE)
            //  we couldn't find a valid path between this open missing connection and another one on the board
            //  that means it's a dead end
            return false;

        // board representation restoration
        if (not_allowed_target_tile != NULL)
            board_representation_matrix[not_allowed_target_tile->absolute_pos.i][not_allowed_target_tile->absolute_pos.j] = temp_removed_representation_infos[0];
        board_representation_matrix[start_tile->absolute_pos.i][start_tile->absolute_pos.j] = temp_removed_representation_infos[1];

        // record end_tile as already checked
        has_already_been_check_matrix[end_tile->absolute_pos.i][end_tile->absolute_pos.j] = true;
    }

    return true;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 * @todo new check idea in addition to those in python project :
 * if the double missing connection still exist after its corresponding piece has been played
 * we know for a fact that no other piece can fill it and thus, the board is discarded
 *
 * I already kinda done it in the comments below, it has to be redesign to check only the tiles of the last added piece
 */

// static bool check_if_double_missing_connection_is_still_fillable(Board *board, Tile *tile_stack)
// {
//     // first identify the type of double missing connection
//     static Direction connection_direction_array[2];
//     static int connection_idx;
//     static bool is_line_shape;
//     static Tile *temp_tile = NULL;

//     temp_tile = tile_stack;
//     connection_idx = 0;
//     while (temp_tile != UNDEFINED_TILE)
//     {
//         if (temp_tile->tile_type = missing_connection)
//         {
//             connection_direction_array[connection_idx] = temp_tile->connection_direction_array[0];
//             connection_idx++;
//         }
//         temp_tile = temp_tile->next;
//     }

//     // Assuming the directions of missing connections are different, do their sum is a bend-shape or a line-shape
//     // only 2 case where the shape formed by the 2 directions can be a line : (RIGHT:0,LEFT:2) (means horizontal line) and (DOWN:1,UP:3) (means vertical line)
//     // otherwise it's a bend shape
//     is_line_shape = (abs((connection_direction_array[0]) - (connection_direction_array[1]))) == 2;

//     // A line-shape double missing connection tile can only exist if line2 2 piece has not been played yet
//     if (is_line_shape && (board->has_line2_2_been_added))
//         return false;

//     // A bend-shape double missing connection tile can only exist if T-piece has not been played yet
//     if (!is_line_shape && (board->has_T_piece_been_added))
//         return false;

//     return true;
// }

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// -------------- Main public function of this whole file ------------------------------------------------------------------

// Function to run all checks that have to be done after a piece was added
// To see if the board is worth continuing or not
// As soon as one of the check don't pass, function discard all other computation and returns
// Let the more likely and easy-to-compute checks be in first to cut down more computation
// Returns int error_code based on the check that didn't pass else 1
int run_all_checks(Board *board)
{
    static Piece *last_added_piece = NULL;

    last_added_piece = (board->piece_array) + board->added_piece_idx_array[board->nb_of_added_pieces - 1];

    if (!check_isolated_tiles_around_piece(board, last_added_piece))
        return ISOLATED_EMPTY_TILE;

    if (board->nb_of_added_pieces > 1)
    {
        if (!check_no_dead_ends(board))
            return DEAD_END;
    }

    if (!check_no_loops(board, last_added_piece))
        return LOOP_PATH;

    return 1;
}