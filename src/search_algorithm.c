/**
 * @file search_algorithm.c
 *
 * @todo add desc
 */

#include <local/search_algorithm.h>

// function to generate all k-combinations of piece_idx_array
// the result is stored in result_comb by reference
// function derived from : https://scvalex.net/posts/cp5/
static int generate_next_combination(const int *piece_idx_array, int *result_comb, int k, int n)
{
    if (k == 0)
        return 0;
    static int i = 0;
    static int comb[MAX_NB_OF_OPEN_POINTS];
    static bool is_init = false;

    if (!is_init)
    {
        for (i = 0; i < k; i++)
            comb[i] = i;
        is_init = true;
    }
    else
    {

        i = k - 1;
        comb[i]++;
        while ((i >= 0) && (comb[i] >= n - k + 1 + i))
        {
            i--;
            comb[i]++;
        }

        if (comb[0] > n - k)
            return 0;

        for (i = i + 1; i < k; ++i)
            comb[i] = comb[i - 1] + 1;
    }

    for (i = 0; i < k; i++)
        result_comb[i] = piece_idx_array[comb[i]];
    return 1;
}

// Function to figure out all possible piece start combinations.
// In the search algorithm we fill the board by adding piece one by one
// starting by pieces with point on their first side, and starting by filling open points in level hints
// But there are a lot more game pieces with a point than point to fill
// That's why we need combinations
static StartCombinations determine_start_combinations(Board *board, LevelHints *level_hints)
{
    StartCombinations start_combinations;

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
        for (piece_idx = 0; piece_idx < NB_OF_PIECES; piece_idx++)
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
    while (generate_next_combination(piece_idx_that_are_playable, start_combinations.combination_array[start_combinations.nb_of_combinations], level_hints->nb_of_open_obligatory_point_tiles, nb_of_remaining_pieces))
        start_combinations.nb_of_combinations++;

    return start_combinations;
}

static void load_combination_deduction_data(Board *board, StartCombinations *start_combinations, LevelHints *level_hints, int combination_idx, int *piece_idx_priority_array, int *nb_of_playable_pieces, bool playable_side_per_piece_idx_mask[][MAX_NB_OF_SIDE_PER_PIECE])
{

    static int i, piece_idx;
    static bool piece_found;

    *nb_of_playable_pieces = 0;

    // add the first piece indexes dictate by start_combinations
    for (i = 0; i < level_hints->nb_of_open_obligatory_point_tiles; i++)
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
    for (piece_idx = 0; piece_idx < NB_OF_PIECES; piece_idx++)
    {
        piece_found = false;
        for (i = 0; i < level_hints->nb_of_open_obligatory_point_tiles; i++)
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

// --------------------------------------------------------------------------------------------------------------------------------------
// Main algorithm sub routines

static void setup_draw(Board *board, int level_num, char *level_num_str)
{
    // Functions only needed because we display things
    sprintf(level_num_str, "%d", level_num);
    setup_display();
    update_board_grid_drawing(board);
    update_board_obligatory_tiles_drawing(board);
    for (int i = 0; i < board->nb_of_added_pieces; i++)
        update_piece_all_drawing((board->piece_array) + board->added_piece_idx_array[i], false);
}

void reset_all_board_pieces(Board *board)
{
    static int piece_idx;
    static Piece *piece;

    for (piece_idx = 0; piece_idx < NB_OF_PIECES; piece_idx++)
    {
        piece = (board->piece_array) + piece_idx;

        piece->current_side_idx = 0;
        piece->current_base_pos = (Vector2_int){0, 0};
        piece->current_rotation_state = 0;
    }
}

static void draw(Board *board, const char *level_num_str)
{
    BeginDrawing();
    ClearBackground(BLACK);
    draw_board(board, false);
    draw_level_num(level_num_str);
    EndDrawing();
}

bool run_algorithm_with_display(int level_num)
{

    LevelHints *level_hints = get_level_hints(level_num);
    Board *board = init_board(level_hints);

    // Functions only needed because we display things
    char level_num_str[4];
    setup_draw(board, level_num, level_num_str);

    StartCombinations start_combinations = determine_start_combinations(board, level_hints);
    int piece_idx_priority_array[NB_OF_PIECES];
    int nb_of_playable_pieces = 0;
    bool playable_side_per_piece_idx_mask[NB_OF_PIECES][MAX_NB_OF_SIDE_PER_PIECE];

    int piece_selected;

    int piece_idx;
    Piece *piece;
    int side_idx;
    Vector2_int base_pos;
    int rotation_state;

    int valid_board_count = 0;

    printf("Setup successful ! \n");

    // Updating and drawing loop for algorithm visualization
    int combination_idx = 0;
    bool skip_current_pos = false;
    reset_all_board_pieces(board);

    while (true)
    {
    next_combination:

        if (combination_idx == start_combinations.nb_of_combinations)
        {
            // case where there is no solution in any combination, we went through them all
            printf("No solution found...\n");
            break;
        }

        piece_selected = 0;
        // reset_all_board_pieces(board);
        skip_current_pos = false;

        // We first need to figure out the priority order list in which pieces will be added one by one, according to current start combination and pieces already added by level hints
        // Which sides are playable per piece, ...
        load_combination_deduction_data(board, &start_combinations, level_hints, combination_idx, piece_idx_priority_array, &nb_of_playable_pieces, playable_side_per_piece_idx_mask);
        // printf("testing new combination.\n");
        while (true)
        {
        next_piece:
            if (piece_selected < 0)
            {
                // case where the first piece used all its positions, which means there are no solution with current combination
                combination_idx++;
                goto next_combination;
            }
            else if (piece_selected == nb_of_playable_pieces)
            {
                // case where the successfully added the last piece to the board
                printf("Solution found !\n");
                goto end;
            }

            piece_idx = piece_idx_priority_array[piece_selected];
            piece = (board->piece_array) + piece_idx;

            for (side_idx = piece->current_side_idx; side_idx < piece->nb_of_sides; side_idx++)
            {
                if (!playable_side_per_piece_idx_mask[piece_idx][side_idx])
                    continue;
                for (base_pos.i = piece->current_base_pos.i; base_pos.i < BOARD_WIDTH; (base_pos.i)++)
                {

                    for (base_pos.j = piece->current_base_pos.j; base_pos.j < BOARD_HEIGHT; (base_pos.j)++)
                    {
                        if (is_position_already_occupied(board, base_pos))
                            continue;

                        for (rotation_state = piece->current_rotation_state; rotation_state < NB_OF_DIRECTIONS; rotation_state++)
                        {
                            if (WindowShouldClose())
                                goto end_end;
                            if (skip_current_pos)
                            {
                                skip_current_pos = false;
                                continue;
                            }

                            if (add_piece_to_board(board, piece_idx, side_idx, base_pos, rotation_state) != 1)
                                continue;
                            if (run_all_checks(board) != 1)
                            {
                                undo_last_piece_adding(board);
                                continue;
                            }
                            // case where we successfully added a piece
                            update_piece_all_drawing(piece, false);
                            piece_selected++;
                            valid_board_count++;
                            printf("new valid board found ! %d\n", valid_board_count);
                            draw(board, level_num_str); // draw only when new board found to make everything faster ?
                            // so there's no point to separate update and draw functions :/
                            goto next_piece;
                        }
                        piece->current_rotation_state = 0; // need update for next iterations
                    }
                    piece->current_base_pos.j = 0;
                }
                piece->current_base_pos.i = 0;
            }
            // the current piece has gone through all its possible positions
            // we need to reset them for later and try to move the previous piece
            piece->current_side_idx = 0;

            piece_selected--;
            if (piece_selected >= 0)
                undo_last_piece_adding(board);
            skip_current_pos = true; // if not, it will find the previous piece will find the same location to fill
        }
    }

end:
    // display last board state until user close the window
    while (!WindowShouldClose())
        draw(board, level_num_str);
end_end:
    CloseWindow();
    free_board(board);
    free(level_hints);

    return true;
}

/**
 * @todo y'a encore des bugs chelous, j'ai l'impression qu'il tourne en boucle sur le niveau 83
 * et que surtout, il n'essaye pas les autres combinations
 */