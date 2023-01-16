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

    return 1;
}