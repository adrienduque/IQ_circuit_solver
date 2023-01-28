/**
 * @file search_algorithm.c
 *
 *
 * Main search algorithm explanation :
 *
 *      "Brute force algorithm with backtracking"
 *
 *      (Another algorithm with backtracking that reminded me of this project : [sudoku solver : https://youtu.be/G_UYXzGuqvM])
 *
 *      First I suggest reading the game rules in the booklet if you didn't have already, I will assume them as knew from now on.
 *      (game rules can be found here too : https://www.smartgames.eu/uk/one-player-games/iq-circuit)
 *
 *      1) First we select a level and see which hints it has, I only implemented the 3 last difficulties :
 *
 *      They consist of pre-added pieces on the board + or/and obligatory tiles on the board, or at least I generalized it like that.
 *
 *      - Expert levels (from 49 to 72  included) : board is completely filled with obligatory tiles of different types (all paths are shown)
 *      - Master levels (from 73 to 96  included) : board has pre-added pieces and obligatory open point tiles (point tiles that are missing, but we know their numbers and positions)
 *      - Wizard levels (from 97 to 120 included) : board only has obligatory open point tiles
 *
 *      2) According to the level hints, we need to choose which pieces will fill the open points, and which pieces won't
 *
 *      It's a way to stay pretty organized, it determines which sides of which pieces we can play and limit the number of possibilities.
 *      (the choosen pieces that fill points can only play their side with a point, other ones can play all their sides except the ones with a point)
 *
 *      (also at this point in time, we assume that we don't have the already played pieces at our disposition (the pre-added pieces by level hints))
 *
 *      As there are a lot more pieces with a point than potential points to fill on the board, we might not choose the right pieces the first time
 *
 *      That is why we need to record all the choices we could have made for the pieces, and explore all of them one at a time.
 *
 *      My algorithm makes up a preprocessed list of combinations for the choosen point pieces, then make an ordered list of pieces to play (starting by the point ones) for each combination.
 *
 *      3) Testing and backtracking (for one choice, one ordedred list)
 *
 *      For each piece, we can define a global position vector on the board, for example composed of (which side, horizontal position, vertical position, rotation)
 *
 *      Basically, the algorithm try every global position of the current piece, and play it as soon as it can.
 *          2 cases :
 *              a. the piece is successfully played -> try the same thing for the next piece in the ordered list
 *              b. the piece can't be played (it reached the end of global position possibilities) -> backtrack and try to move the previous piece in the ordered list
 *              (the piece that can't be played is also reset to the base global position to try all over again in another configuration of the previous pieces.)
 *
 *          Each piece keeps track of its global position, and moves from it when we backtrack, it doesn't restart from the base global position.
 *
 *      2 cases :
 *          a. the algorithm has successfully played the last piece and try to move on to the next one -> there isn't a next one, it has found the solution to the level !
 *          b. the algorithm can't play the first piece and try to backtrack to the previous one -> there isn't a previous one, the choice it made about the point pieces was not the right one, try all over again in the next choice (next combination).
 *
 *      With this algorithm, we can safely say that it will eventually try all position possibilities, as the solution is one of them, it can find the solution 100% of the time.
 *
 *      4) How does it know when a piece can be added to the board or not ? -> it rather knows the cases where a piece can't be added, and by default it can
 *
 *      a. we can skip obvious position of a piece (if the side choosen is set to not be playable : see 2)) (or if we know the board is already filled at the horizontal/vertical position we want to try)
 *
 *      b. The method to add a piece to the board has a few checks before the piece is blit to the board, (connection checking, superposition of tiles, match of level hints,...) see board.c for more informations  (that is what I call "pre-adding checks")
 *      (of course if one of the checks doesn't pass, the piece is not added to the board)
 *
 *      c. After the piece has been successfully added, a list of checks is applied to the board (do the paths contains loops ? (which are not allowed), is there an isolated empty tile ?(which we know can't be filled), ...) see check_board.c (that is what I call "post-adding checks")
 *      (if one of these checks doesn't pass, the piece is instantly removed from the board, it's as if it was never added)
 *
 * Conclusion :
 *
 *      We can see this as a depth first search algorithm, in a tree without loops, in which we search for the right path from root to the correct leaf node.
 *      Where each middle node of the tree is an incomplete state of the board (board that don't have all the game pieces on it).
 *      Each leaf node is a complete state of the board (all the pieces are here), but there is only 1 valid complete board per level (we can imagine many of them are complete but with superposed pieces for example, thus invalid)
 *      The current piece the algorithm is trying to add, represents the depth in the tree.
 *      Each combination is a new tree.
 *
 *      Having more and smarter checks to not add a piece, is the way we cut down computational costs and time. By closing a node, we don't have to explore its children.
 *
 *      Smarter checks will detect earlier that a board is not completeable <=> the higher on the tree, we close nodes, the lesser remaining nodes to explore.
 *
 *      While this project is still in development, we can mesure the pure logic performance of the algorithm by counting the number of valid boards that it had to go through to find the final one that is the solution to the level.
 *      It's like counting the number of explored nodes that the algorithm didn't close.
 *
 *      Of course, the more checks it has to apply to a board, the more computation and time nedded on each node.
 *      It's a trade-off and one that is almost always worth.
 *
 *      See the evolution of my algorithm performance stats in the excel file in showcase_assets folder.
 *
 *      In the first complete version of the algorithm, the number of valid boards goes to tens of millions (level 120) for example.
 *      There isn't much post-adding checks yet.
 *
 */

#include <local/search_algorithm.h>
#include <time.h>

// ----------------- Main algorithm data pre-processing ----------------------------------------------------------------------------

/**
 * @struct StartCombinations
 * struct to store all the combinations of the different choices we can make,
 * when we are choosing which pieces will fill the open points of the level hints
 * see search_algorithm.c description
 */
typedef struct StartCombinations
{

    int combination_array[MAX_NB_OF_COMBINATIONS][MAX_NB_OF_OPEN_POINTS];
    int nb_of_combinations;

} StartCombinations;

// Function to figure out all possible piece start combinations.
// In the search algorithm we fill the board by adding piece one by one
// starting by pieces with point on their first side, and starting by filling open points in level hints
// But there are a lot more game pieces with a point than point to fill
// That's why we need to test different combinations
static StartCombinations determine_start_combinations(Board *board)
{
    StartCombinations start_combinations;

    if (board->nb_of_open_obligatory_point_tiles == 0)
    {
        // special case where we don't need to test different combinations
        // to make it part of the general case for the main algorithm, we need to do this:
        start_combinations.nb_of_combinations = 1;
        return start_combinations;
    }

    // temp variables
    static int piece_idx;
    static Piece *piece;
    static bool piece_found;

    // main data variables
    static int piece_idx_that_have_point_on_first_side_array[NB_OF_PIECES];
    static int nb_of_point_pieces = 0;

    static int piece_idx_that_are_playable[NB_OF_PIECES];
    static int nb_of_remaining_pieces;

    // 1) Figure out the list of starting pieces (the one that have a point on their first side)
    // do only this computation once, because it is the same for every level
    if (nb_of_point_pieces == 0)
    {
        // for (piece_idx = 0; piece_idx < NB_OF_PIECES; piece_idx++)
        for (piece_idx = NB_OF_PIECES - 1; piece_idx >= 0; piece_idx--)
        {
            piece = (board->piece_array) + piece_idx;
            if (piece->has_point_on_first_side)
            {
                piece_idx_that_have_point_on_first_side_array[nb_of_point_pieces] = piece_idx;
                nb_of_point_pieces++;
            }
        }
    }

    // 2) Remove already played pieces by level hints from the actual starting list
    nb_of_remaining_pieces = 0;
    for (int i = 0; i < nb_of_point_pieces; i++)
    {
        piece_idx = piece_idx_that_have_point_on_first_side_array[i];
        piece_found = false;
        for (int j = 0; j < board->nb_of_added_pieces; j++)
        {
            if (board->added_piece_idx_array[j] == piece_idx)
            {
                piece_found = true;
                break;
            }
        }
        if (!piece_found)
        {
            piece_idx_that_are_playable[nb_of_remaining_pieces] = piece_idx;
            nb_of_remaining_pieces++;
        }
    }

    // 3) Figure out the all the possible combinations from this list, depending on the nb of open points of the level
    start_combinations.nb_of_combinations = 0;
    while (generate_next_combination(piece_idx_that_are_playable, nb_of_remaining_pieces, start_combinations.combination_array[start_combinations.nb_of_combinations], board->nb_of_open_obligatory_point_tiles))
        start_combinations.nb_of_combinations++;

    return start_combinations;
}

// Function to figure out the order in which piece need to be added to the board according to the current combination
// -> loaded by reference in "piece_idx_priority_array" + length of it in "nb_of_playable_pieces"
// Also load by reference which piece sides are playable
// as a combination is the current set of chosen point piece, they only can play their side with a point
// other pieces are forced to play their sides without a point (as we can't add point tiles that don't belong to level hints, it is written in gamerules)
static void load_combination_data(Board *board, StartCombinations *start_combinations, int combination_idx, int *piece_idx_priority_array, int *nb_of_playable_pieces, bool playable_side_per_piece_idx_mask[][MAX_NB_OF_SIDE_PER_PIECE])
{

    static int i, piece_idx;
    static bool piece_found;

    *nb_of_playable_pieces = 0;

    // add the first piece indexes dictate by start_combinations
    for (i = 0; i < board->nb_of_open_obligatory_point_tiles; i++)
    {
        piece_idx = start_combinations->combination_array[combination_idx][i];
        piece_idx_priority_array[*nb_of_playable_pieces] = piece_idx;
        (*nb_of_playable_pieces)++;

        // pieces that come from this category are constrained to play only their side with a point
        playable_side_per_piece_idx_mask[piece_idx][0] = true;
        playable_side_per_piece_idx_mask[piece_idx][1] = false;
        playable_side_per_piece_idx_mask[piece_idx][2] = false;
    }

    // add the remaining pieces (all pieces except those who are already in the list or already played by level hints)
    // for (piece_idx = 0; piece_idx < NB_OF_PIECES; piece_idx++)
    for (piece_idx = NB_OF_PIECES - 1; piece_idx >= 0; piece_idx--)
    {
        piece_found = false;
        for (i = 0; i < board->nb_of_open_obligatory_point_tiles; i++)
        {
            if (piece_idx_priority_array[i] == piece_idx)
            {
                piece_found = true;
                break;
            }
        }
        if (piece_found)
            continue;
        for (i = 0; i < board->nb_of_added_pieces; i++)
        {
            if (board->added_piece_idx_array[i] == piece_idx)
            {
                piece_found = true;
                break;
            }
        }

        if (piece_found)
            continue;

        piece_idx_priority_array[*nb_of_playable_pieces] = piece_idx;
        (*nb_of_playable_pieces)++;

        // pieces that come from this category are constrained to play only their sides without a point
        playable_side_per_piece_idx_mask[piece_idx][0] = !(board->piece_array[piece_idx].has_point_on_first_side);
        playable_side_per_piece_idx_mask[piece_idx][1] = true;
        playable_side_per_piece_idx_mask[piece_idx][2] = true;
    }
}

// ----------------- Main algorithm mini sub routines ----------------------------------------------------------------------------

static void setup_draw(Board *board, int level_num, char *level_num_str)
{
    // Functions only needed because we display things
    sprintf(level_num_str, "%d", level_num);
    setup_display((BOARD_WIDTH + 2) * tile_px_width, (BOARD_HEIGHT + 2) * tile_px_width);
    update_board_static_drawing(board);
}

static void draw(Board *board, const char *level_num_str)
{
    BeginDrawing();
    ClearBackground(BLACK);
    draw_board(board, false);
    draw_level_num(level_num_str);
    // DrawFPS(100, 10);
    EndDrawing();
}

// Function to only check if a position is already taken by a normal tile on the board
static bool is_position_already_occupied(Board *board, Vector2_int *base_pos)
{
    return (extract_normal_tile_at_pos(board, base_pos) != UNDEFINED_TILE);
}

// -------------------------------------------------------------------------------------------------------------------------------

// Main function
void run_algorithm_with_display(int level_num, int FPS)
{

    // Main data variables init
    LevelHints *level_hints = get_level_hints(level_num);
    Board *board = init_board(level_hints);

    // Preprocessed constants of current setup
    StartCombinations start_combinations = determine_start_combinations(board);

    // Functions only needed because we display things
    char level_num_str[4];
    setup_draw(board, level_num, level_num_str);
    static bool enable_slow_operations = false;
    if (FPS != 0)
    {
        SetTargetFPS(FPS);
        enable_slow_operations = true;
    }

    // data placeholders for each combination test
    int piece_idx_priority_array[NB_OF_PIECES];
    int nb_of_playable_pieces;
    bool playable_side_per_piece_idx_mask[NB_OF_PIECES][MAX_NB_OF_SIDE_PER_PIECE];

    // variable to explore current piece_idx_priority_array
    // basically the depth at which the algorithm currently is, in the search tree
    int piece_selected;

    // "add_piece_to_board" input parameters
    int piece_idx;
    int side_idx;
    Vector2_int base_pos;
    int rotation_state;

    // variable to count valid boards and mesure logic performance, see this file description
    int valid_board_count = 0;

    // timing the algorithm (loop only part)
    clock_t begin, end;
    double time_spent;
    begin = clock();

    // convenience placeholder variables used in the loop
    Piece *piece;
    bool backtrack_iteration = false;
    bool solved = false;

    // Updating and drawing loop for algorithm visualization
    for (int combination_idx = 0; combination_idx < start_combinations.nb_of_combinations; combination_idx++)
    {
        // the algorithm needs to know which order to add the pieces to the board following the current combination informations

        // and also which piece sides it can play, as a combination is the current set of chosen point piece, they only can play their side with a point
        // other pieces are forced to play their sides without a point (as we can't add point tiles that don't belong to level hints, it is written in gamerules)
        // the algorithm can work without this last informations, but it is meant to skip obviously useless iterations
        load_combination_data(board, &start_combinations, combination_idx, piece_idx_priority_array, &nb_of_playable_pieces, playable_side_per_piece_idx_mask);

        // Setup the exploration of the current combination
        piece_selected = 0;
        backtrack_iteration = false;

        // Loop to explore the current combination
        // The backtracking part is made by decrementing "piece_selected"
        while (true)
        {

        next_piece:

            // --- Edges cases when piece_selected step out of valid "piece_idx_priority_array" indexes, in both directions
            if (piece_selected < 0)
                // case where the first piece used all its position possibilities, which means there are no solution with current combination
                break;

            else if (piece_selected == nb_of_playable_pieces)
            {
                // case where the successfully added the last piece to the board
                solved = true;
                goto end_loop;
            }
            // ---

            // if we are currently backtracking, the piece needs to be removed
            // before being re-added
            if (backtrack_iteration)
                undo_last_piece_adding(board);

            // Part where the algorithm try all current piece position possibilities
            // Starting from its previous position

            // setup
            piece_idx = piece_idx_priority_array[piece_selected];
            piece = (board->piece_array) + piece_idx;

            // loop
            for (side_idx = piece->current_side_idx; side_idx < piece->nb_of_sides; side_idx++)
            {
                // only play forced sides (prievously determined by "load_combination_data")
                if (!playable_side_per_piece_idx_mask[piece_idx][side_idx])
                    continue;

                for (base_pos.i = piece->current_base_pos.i; base_pos.i < BOARD_WIDTH; (base_pos.i)++)
                {
                    for (base_pos.j = piece->current_base_pos.j; base_pos.j < BOARD_HEIGHT; (base_pos.j)++)
                    {
                        // don't even consider adding the piece at this position if there's already a normal tile on the board
                        if (is_position_already_occupied(board, &base_pos))
                            continue;

                        for (rotation_state = piece->current_rotation_state; rotation_state < piece->side_array[side_idx].max_nb_of_rotations; rotation_state++)
                        {
                            if (WindowShouldClose())
                                goto quit_algorithm;

                            // when we backtrack, we need to increment the previous piece overall position by 1
                            // (if not, the piece will be added where it was just removed)
                            // we do it, by skipping 1 iteration in the innermost loop
                            if (backtrack_iteration)
                            {
                                backtrack_iteration = false;
                                continue;
                            }

                            // Board pre-adding, adding piece, and post-adding checks
                            if (add_piece_to_board(board, piece_idx, side_idx, base_pos, rotation_state) != 1)
                                continue;
                            if (run_all_checks(board, enable_slow_operations) != 1)
                            {
                                undo_last_piece_adding(board);
                                continue;
                            }
                            // case where we successfully added a piece
                            update_piece_all_drawing(piece, false, false);
                            piece_selected++;
                            valid_board_count++;
                            if (enable_slow_operations)
                                printf("new valid board found ! %d\n", valid_board_count);
                            draw(board, level_num_str); // draw only when new board found to make everything faster ? -> this is so fast wtf
                            // so there's no point to separate update_drawing and draw functions :/
                            // my whole display.c design intention was "update only data when we need to but draw at each iteration even with no updates"
                            // that means there is a lot of useless drawing cache variables
                            goto next_piece;
                        }
                        piece->current_rotation_state = 0;
                    }
                    piece->current_base_pos.j = 0;
                }
                piece->current_base_pos.i = 0;
            }
            piece->current_side_idx = 0;
            // the current piece has gone through all its possible positions
            // we need to backtrack (try to move the previous piece)
            piece_selected--;
            backtrack_iteration = true;
        }
    }

end_loop:
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

#ifndef AUTOMATED_RUNS

    if (solved)
        printf("Solution found !\n");
    else
        printf("No solution found...\n");
    printf("Time : %.3f seconds\n", time_spent);
    printf("Number of valid boards : %d\n", valid_board_count);

    // display last board state until user close the window
    while (!WindowShouldClose())
        draw(board, level_num_str);

#else
    printf("%3d : ", level_num);
    if (solved)
        printf("solved -> ");
    else
        printf("unsolved -> ");
    printf("%d | %d\n", valid_board_count, (int)(time_spent * 1000));

#endif

quit_algorithm:
    CloseWindow();
    free(board);
    free(level_hints);
}

// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------

// Main function without the hassle of drawing everything and even printing to the console
// Just to see how fast it can go for fun
void run_algorithm_without_display(int level_num)
{

    // Main data variables init
    LevelHints *level_hints = get_level_hints(level_num);
    Board *board = init_board(level_hints);

    // Preprocessed constants of current setup
    StartCombinations start_combinations = determine_start_combinations(board);

    // data placeholders for each combination test
    int piece_idx_priority_array[NB_OF_PIECES];
    int nb_of_playable_pieces;
    bool playable_side_per_piece_idx_mask[NB_OF_PIECES][MAX_NB_OF_SIDE_PER_PIECE];

    // variable to explore current piece_idx_priority_array
    // basically the depth at which the algorithm currently is, in the search tree
    int piece_selected;

    // "add_piece_to_board" input parameters
    int piece_idx;
    int side_idx;
    Vector2_int base_pos;
    int rotation_state;

    // variable to count valid boards and mesure logic performance, see this file description
    int valid_board_count = 0;

    // timing the algorithm (loop only part)
    clock_t begin, end;
    double time_spent;
    begin = clock();

    // convenience placeholder variables used in the loop
    Piece *piece;
    bool backtrack_iteration = false;
    bool solved = false;

    // Updating and drawing loop for algorithm visualization
    for (int combination_idx = 0; combination_idx < start_combinations.nb_of_combinations; combination_idx++)
    {
        // the algorithm needs to know which order to add the pieces to the board following the current combination informations

        // and also which piece sides it can play, as a combination is the current set of chosen point piece, they only can play their side with a point
        // other pieces are forced to play their sides without a point (as we can't add point tiles that don't belong to level hints, it is written in gamerules)
        // the algorithm can work without this last informations, but it is meant to skip obviously useless iterations
        load_combination_data(board, &start_combinations, combination_idx, piece_idx_priority_array, &nb_of_playable_pieces, playable_side_per_piece_idx_mask);

        // Setup the exploration of the current combination
        piece_selected = 0;
        backtrack_iteration = false;

        // Loop to explore the current combination
        // The backtracking part is made by decrementing "piece_selected"
        while (true)
        {

        next_piece:

            // --- Edges cases when piece_selected step out of valid "piece_idx_priority_array" indexes, in both directions
            if (piece_selected < 0)
                // case where the first piece used all its position possibilities, which means there are no solution with current combination
                break;

            else if (piece_selected == nb_of_playable_pieces)
            {
                // case where the successfully added the last piece to the board
                solved = true;
                goto end_loop;
            }
            // ---

            // if we are currently backtracking, the piece needs to be removed
            // before being re-added
            if (backtrack_iteration)
                undo_last_piece_adding(board);

            // Part where the algorithm try all current piece position possibilities
            // Starting from its previous position

            // setup
            piece_idx = piece_idx_priority_array[piece_selected];
            piece = (board->piece_array) + piece_idx;

            // loop
            for (side_idx = piece->current_side_idx; side_idx < piece->nb_of_sides; side_idx++)
            {
                // only play forced sides (prievously determined by "load_combination_data")
                if (!playable_side_per_piece_idx_mask[piece_idx][side_idx])
                    continue;

                for (base_pos.i = piece->current_base_pos.i; base_pos.i < BOARD_WIDTH; (base_pos.i)++)
                {
                    for (base_pos.j = piece->current_base_pos.j; base_pos.j < BOARD_HEIGHT; (base_pos.j)++)
                    {
                        // don't even consider adding the piece at this position if there's already a normal tile on the board
                        if (is_position_already_occupied(board, &base_pos))
                            continue;

                        for (rotation_state = piece->current_rotation_state; rotation_state < piece->side_array[side_idx].max_nb_of_rotations; rotation_state++)
                        {

                            // when we backtrack, we need to increment the previous piece overall position by 1
                            // (if not, the piece will be added where it was just removed)
                            // we do it, by skipping 1 iteration in the innermost loop
                            if (backtrack_iteration)
                            {
                                backtrack_iteration = false;
                                continue;
                            }

                            // Board pre-adding, adding piece, and post-adding checks
                            if (add_piece_to_board(board, piece_idx, side_idx, base_pos, rotation_state) != 1)
                                continue;
                            if (run_all_checks(board, false) != 1)
                            {
                                undo_last_piece_adding(board);
                                continue;
                            }
                            // case where we successfully added a piece
                            piece_selected++;
                            valid_board_count++;
                            // printf("new valid board found ! %d\n", valid_board_count);
                            goto next_piece;
                        }
                        piece->current_rotation_state = 0;
                    }
                    piece->current_base_pos.j = 0;
                }
                piece->current_base_pos.i = 0;
            }
            piece->current_side_idx = 0;
            // the current piece has gone through all its possible positions
            // we need to backtrack (try to move the previous piece)
            piece_selected--;
            backtrack_iteration = true;
        }
    }

end_loop:
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

#ifndef AUTOMATED_RUNS

    if (solved)
        printf("Solution found!\n");
    else
        printf("No solution found...\n");
    printf("Time : %.3f seconds\n", time_spent);
    printf("Number of valid boards : %d\n", valid_board_count);

    // Display only the last board state
    char level_num_str[4];
    setup_draw(board, level_num, level_num_str);

    // display last board state until user close the window
    while (!WindowShouldClose())
        draw(board, level_num_str);

    CloseWindow();

#else
    printf("%3d : ", level_num);
    if (solved)
        printf("solved -> ");
    else
        printf("unsolved -> ");
    printf("%d | %d\n", valid_board_count, (int)(time_spent * 1000));

#endif

    free(board);
    free(level_hints);
}

// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------

//@todo : run_algorithm_with_extra_display