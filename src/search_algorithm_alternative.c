/**
 *
 * @author Adrien Duqué (@adrienduque)
 * Original Github repository : https://github.com/adrienduque/IQ_circuit_solver
 *
 * @file search_algorithm_alternative.c
 *
 * Quick dirty test for a different idea than the one for the next version of master branch
 *
 * @note : functions originally copied from search_algorithm.c > run_algorithm_with_extra_display
 */

#include <time.h> // clock_t, clock, and CLOCKS_PER_SEC
#include <stdbool.h>
#include <stdio.h>  // printf, sprintf
#include <stdlib.h> // free

#include <raylib/raylib.h> // WindowShouldClose, CloseWindow, BeginDrawing, EndDrawing, ClearBackground, DrawFPS, SetTargetFPS

#include <local/utils.h>       // Vector2_int, generate_next_combination and defines
#include <local/piece_data.h>  // Tile, Side, Piece and defines
#include <local/level_data.h>  // LevelHints, and defines
#include <local/board.h>       // Board, helper functions and defines
#include <local/check_board.h> // run_all_checks
#include <local/display.h>     // tile_px_width, and other drawing functions

#include <local/search_algorithm.h>

static bool playable_side_per_piece_idx_mask[NB_OF_PIECES][MAX_NB_OF_SIDE_PER_PIECE];

static void prepare_piece_idx_priority_array(Board *board, int piece_idx_priority_array[NB_OF_PIECES], int *nb_of_playable_pieces)
{
    static bool piece_found;
    static int default_piece_idx_priority_array[NB_OF_PIECES] = {
        Z_PIECE,
        SQUARE,
        CORNER_1,
        CORNER_2,
        T_PIECE,
        L_PIECE,
        LINE3_2,
        LINE3_1,
        LINE2_2,
        LINE2_1};

    static int piece_idx;

    for (int i = 0; i < NB_OF_PIECES; i++)
    // for (int i = NB_OF_PIECES - 1; i >= 0; i--)
    {
        piece_idx = default_piece_idx_priority_array[i];
        // piece_idx = i;

        piece_found = false;
        for (int j = 0; j < board->nb_of_added_pieces; j++)
        {
            if (piece_idx == board->added_piece_idx_array[j])
            {
                piece_found = true;
                break;
            }
        }
        if (piece_found)
            continue;
        piece_idx_priority_array[*nb_of_playable_pieces] = piece_idx;
        (*nb_of_playable_pieces)++;
    }
}

// returns 0 -> corner_1 has been requested but doesn't fit
// returns 1 -> corner_1 doesn't have been requested
// returns 2 -> corner_1 has been requested and it fit !
static int is_corner_1_case_resolved(Board *board, bool enable_slow_operations)
{
    static int rotation_state;

    if (board->has_corner_1_been_added || !is_pos_valid(&(board->requested_corner_1_adding_position)))
        // corner_1 is already on the board or did not have been requested this time
        return 1;

    // case where the corner_1 adding has been requested
    // if it's not successfully added, we must return false
    for (rotation_state = 0; rotation_state < NB_OF_DIRECTIONS; rotation_state++)
    {
        if (add_piece_to_board(board, CORNER_1, 0, board->requested_corner_1_adding_position, rotation_state) != 1)
            continue;
        if (run_all_checks(board, enable_slow_operations) != 1)
        {
            undo_last_piece_adding(board);
            continue;
        }
        update_piece_all_drawing((board->piece_array) + CORNER_1, false, false);
        return 2;
    }

    set_invalid_pos(&(board->requested_corner_1_adding_position));
    return 0;
}

static void setup_extra_draw(Board *board)
{
    // Functions only needed because we display things
    setup_display((BOARD_WIDTH + 9) * tile_px_width, (BOARD_HEIGHT + 5) * tile_px_width);
    update_board_static_drawing(board);

    for (int i = 0; i < NB_OF_PIECES; i++)
        playable_side_per_piece_idx_mask[i][0] = true;
}

static void extra_draw(Board *board, int level_num, int piece_idx_priority_array[NB_OF_PIECES], int piece_selected, int nb_of_playable_pieces)
{

    BeginDrawing();
    ClearBackground(BLACK);
    draw_board(board);
    draw_piece_priority_array(piece_idx_priority_array, piece_selected, nb_of_playable_pieces, playable_side_per_piece_idx_mask);
    draw_level_num(level_num);
    EndDrawing();
}

void run_alternative_algorithm(int level_num, int FPS)
{

    // Main data variables init
    LevelHints *level_hints = get_level_hints(level_num);
    Board *board = init_board(level_hints);

    // Functions only needed because we display things
    setup_extra_draw(board);

    static bool enable_slow_operations = false;

    // when set to 0, it's in fact unlimited FPS
    SetTargetFPS(FPS);
    if (FPS != 0)
        enable_slow_operations = true;

    int nb_of_playable_pieces = 0;
    int piece_idx_priority_array[NB_OF_PIECES];

    prepare_piece_idx_priority_array(board, piece_idx_priority_array, &nb_of_playable_pieces);

    // variable to explore piece_idx_priority_array
    // basically the depth at which the algorithm currently is, in the search tree
    int piece_selected = 0;

    // "add_piece_to_board" input parameters
    int piece_idx;

    // Variables to retain where each piece was previously added to backtrack from it
    // this is core to the main algorithm, a feature that was made possible by Piece::current_** members previously
    // but "is_corner_1_case_resovled" function is corrupting these members values, skipping important board states
    // This is my bad not doing thing in a modular way in the past, or at least not enough
    PieceAddInfos current_pos_array[NB_OF_PIECES];
    PieceAddInfos *current_pos;

    for (int i = 0; i < NB_OF_PIECES; i++)
    {
        current_pos_array[i].piece_idx = 0; // we don't even need it
        current_pos_array[i].base_pos = (Vector2_int){0, 0};
        current_pos_array[i].side_idx = 0;
        current_pos_array[i].rotation_state = 0;
    }

    // when a piece is successfully added with the corner_1 at the same time
    //  (passing the check of "is_corner_1_case_resolved")
    //  we might later backtrack to it, thus removing it, to try to play it in an other way
    //  we have to remove corner_1 with it !
    int piece_selected_that_added_corner_1_with_it = -1;
    int return_value;

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

    // Loop to explore the current combination
    // The backtracking part is made by decrementing "piece_selected"
    while (true)
    {

    next_piece:

        // --- Edges cases when piece_selected step out of valid "piece_idx_priority_array" indexes, in both directions
        if (piece_selected < 0)
        {
            // case where the first piece used all its position possibilities, which means there are no solution
            break;
        }

        else if (piece_selected == nb_of_playable_pieces)
        {
            // case where the successfully added the last piece to the board
            solved = true;
            break;
        }
        // ---

        // setup
        piece_idx = piece_idx_priority_array[piece_selected];

        // Special cases when corner_1 is selected as a normal piece part of the priority list
        if (piece_idx == CORNER_1)
        {

            if (!backtrack_iteration && board->has_corner_1_been_added)
            {
                // skip adding corner 1 normally, if the piece was already added by a previous "is_corner_1_case_resolved" function call
                piece_selected++;
                goto next_piece;
            }
            else if (backtrack_iteration && piece_selected_that_added_corner_1_with_it != -1)
            {
                // skip removing corner 1 normally, because it will be removed with the piece that added it with a "is_corner_1_case_resolved" function call
                piece_selected--;
                goto next_piece;
            }
        }

        // if we are currently backtracking, the piece needs to be removed
        // before being re-added
        if (backtrack_iteration)
        {
            undo_last_piece_adding(board);

            if (piece_selected == piece_selected_that_added_corner_1_with_it)
            {
                undo_last_piece_adding(board); // also remove corner_1
                piece_selected_that_added_corner_1_with_it = -1;
            }
        }

        // Part where the algorithm try all current piece position possibilities
        // Starting from its previous position

        piece = (board->piece_array) + piece_idx;
        current_pos = current_pos_array + piece_idx;

        // loop
        for (; (current_pos->side_idx) < piece->nb_of_sides; (current_pos->side_idx)++)
        {
            for (; (current_pos->base_pos.i) < BOARD_WIDTH; (current_pos->base_pos.i)++)
            {
                for (; (current_pos->base_pos.j) < BOARD_HEIGHT; (current_pos->base_pos.j)++)
                {
                    // don't even consider adding the piece at this position if there's already a normal tile on the board
                    if (is_position_already_occupied(board, &(current_pos->base_pos)))
                        continue;

                    for (; (current_pos->rotation_state) < piece->side_array[(current_pos->side_idx)].max_nb_of_rotations; (current_pos->rotation_state)++)
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
                        if (add_piece_to_board(board, piece_idx, (current_pos->side_idx), (current_pos->base_pos), (current_pos->rotation_state)) != 1)
                            continue;
                        if (run_all_checks(board, enable_slow_operations) != 1)
                        {
                            undo_last_piece_adding(board);
                            continue;
                        }

                        // special case of corner_1
                        return_value = is_corner_1_case_resolved(board, enable_slow_operations);
                        if (!return_value)
                        {
                            // we requested adding corner_1 as part of a fit check
                            // and it didn't pass
                            undo_last_piece_adding(board);
                            continue;
                        }
                        else if (return_value == 2)
                        {
                            // we successfully added corner_1 on a missing connection superposed to an open level point
                            piece_selected_that_added_corner_1_with_it = piece_selected;
                            valid_board_count++; // to not cheat on this stat
                        }

                        // case where we successfully added a piece
                        update_piece_all_drawing(piece, false, false);

                        piece_selected++;
                        valid_board_count++;
                        if (enable_slow_operations)
                            printf("new valid board found ! %d\n", valid_board_count);
                        extra_draw(board, level_num, piece_idx_priority_array, piece_selected, nb_of_playable_pieces);

                        goto next_piece;
                    }
                    current_pos->rotation_state = 0;
                }
                current_pos->base_pos.j = 0;
            }
            current_pos->base_pos.i = 0;
        }
        current_pos->side_idx = 0;
        // the current piece has gone through all its possible positions
        // we need to backtrack (try to move the previous piece)
        piece_selected--;
        backtrack_iteration = true;
    }

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
        extra_draw(board, level_num, piece_idx_priority_array, piece_selected, nb_of_playable_pieces);

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
