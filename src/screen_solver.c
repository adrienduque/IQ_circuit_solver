/**
 * @author Adrien Duqué (@adrienduque)
 * Original Github repository : https://github.com/adrienduque/IQ_circuit_solver
 *
 * @file screen_level_select.c
 * @see screens.h
 *
 * File containing Update and Draw functions for the level solver screen, see screens.h and raylib game templates
 *
 * Adaptation from search_algorithm.c > run_algorithm_with_extra_display() to the classic Update/Draw loop form factor here
 * see search_algorithm.c description for an explanation of the algorithm, and later README.md for detailled explanation
 */

/**
 * @todo can i make this screen more fluid if I display board state where a piece was just removed ?
 *
 * and update README with new visuals steps by steps, have a better example of the backtrack algorithm
 */

#include <stdbool.h>
#include <stdlib.h> // NULL

#include <raylib/raylib.h>
#include <raylib/rlgl.h> // rlDrawRenderBatchActive
#include <raylib/raygui.h>

#include <raylib/screens.h>

#include <local/board.h> // Board
#include <local/level_data.h>
#include <local/piece.h>
#include <local/check_board.h> // run_all_checks
#include <local/display.h>
#include <local/utils.h>
#include <local/search_algorithm.h>

// algorithm helper functions
static void setup_next_combination(void);
static void setup_previous_piece(void);
static void setup_next_piece(void);

// custom frame management helper functions
static void set_target_fps(void);
static void update_inputs(void);

// main processed data memory
static Board *board;

// level data memory
static LevelHints *level_hints;

// preprocessed informations per level
// see search_algorithm.c > determine_start_combinations function
static StartCombinations start_combinations;

// preprocessed informations per combination
// see search_algorithm.c > load_combination_data function
static int piece_priority_array[NB_OF_PIECES];
static int nb_of_playable_pieces;
static bool playable_side_per_piece_idx_mask[NB_OF_PIECES][MAX_NB_OF_SIDE_PER_PIECE];

// Variables that represent the internal state of the algorithm
static int combination_idx;  // current combination index
static int piece_selected;   // index of piece_priority_array
static int piece_idx;        // current piece index ( always set to := piece_priority_array[piece_selected])
static Piece *current_piece; // current piece pointer

static bool is_backtrack_iteration;    // to flag update iteration where we want to replace the previous piece
static bool enable_slow_checks;        // see check_board.c > run_all_checks function (disabled only if the FPS is unlimited)
static bool manual_frame_unwind_mode;  // to flag if the user has to manually go through frames (by pressing spacebar)
static bool successful_ending, ending; // to flag algorithm ending and result

// Variables for custom frame and input management
// lower fps are now emulated (update cycles are skipped when necessary)
static int frame_count, frame_update_frequency;
static double previous_time;
static int fps_choice, previous_fps_choice, target_fps;

// Variables that hold performance measures of the algorithm
static double start_time, total_time;
static int valid_board_count;

// classic variable that allow screen switching
static int finishScreen;

void InitSolverScreen(void)
{
    level_hints = get_level_hints(level_num_selected);
    board = init_board(level_hints);
    update_board_static_drawing(board);

    start_combinations = determine_start_combinations(board);

    combination_idx = -1;
    setup_next_combination();

    ending = false;
    successful_ending = false;

    frame_count = -1;

    previous_fps_choice = -1;

    start_time = GetTime();
    previous_time = start_time;
    valid_board_count = 0;

    finishScreen = 0;
}

void UpdateSolverScreen(void)
{
    frame_count++;
    update_inputs();

    if (finishScreen)
        return;

    if (manual_frame_unwind_mode && !IsKeyPressed(KEY_SPACE))
        // allow to go through the rest of the function only if spacebar has been pressed in manual mode
        return;

    if (frame_count % frame_update_frequency != 0)
        // don't update the frame at a given frequency to emulate slow down of the visualization
        return;
    frame_count = 0;

// With the newest update, whenever this update function returns, a new frame is drawn
// to prevent useless / unwanted draw, some return calls became gotos
// also see the last line of this update function
// (a new frame is found in a lot shorter period of time than the time needed between each frames (at a decent DEFAULT_FPS))
algo_beginning:

    if (ending)
        // we don't have to update anything more
        return;

    if (piece_selected < 0)
    {
        // end of play possibilities for this combination, try to get next one
        setup_next_combination();
        return; // draw the frame if a new combination is being tested
    }
    else if (piece_selected >= nb_of_playable_pieces)
    {
        // the last piece has been successfully added to the board
        ending = true;
        total_time = GetTime() - start_time;
        successful_ending = true;
        return;
    }

    // main case where piece_selected is in playable range 0 <= piece_selected < nb_of_playable_pieces

    if (is_backtrack_iteration)
        // remove the piece from the board before trying to add it again
        undo_last_piece_adding(board);

    // Incrementing current_piece positionning test variables in nested while loops
    //      because we want to start / restart from previous position of the piece, and increment from it
    //      but limit the incrementation
    //      and only when the limit is reached, reset the state of the position variable
    // It has the effect to work kind of like a python generator

    while (current_piece->current_side_idx < current_piece->nb_of_sides)
    {
        // skip the current side if the side was set to be not playable in this combination
        if (!playable_side_per_piece_idx_mask[piece_idx][current_piece->current_side_idx])
        {
            (current_piece->current_side_idx)++;
            continue;
        }

        while (current_piece->current_base_pos.i < BOARD_WIDTH)
        {
            while (current_piece->current_base_pos.j < BOARD_HEIGHT)
            {
                // don't even consider adding the piece at this position (i,j) if there's already a normal tile on the board
                if (is_position_already_occupied(board, &(current_piece->current_base_pos)))
                {
                    (current_piece->current_base_pos.j)++;
                    continue;
                }

                while (current_piece->current_rotation_state < current_piece->side_array[current_piece->current_side_idx].max_nb_of_rotations)
                {
                    // when we backtrack, we need to increment the previous piece overall position by 1
                    // (if not, the piece will be added where it was just removed on the board)
                    // we do it, by skipping 1 iteration in the innermost loop
                    if (is_backtrack_iteration)
                    {
                        is_backtrack_iteration = false;
                        (current_piece->current_rotation_state)++;
                        continue;
                    }

                    // main tests here

                    // pre-adding checks
                    if (add_piece_to_board(board, piece_idx, current_piece->current_side_idx, current_piece->current_base_pos, current_piece->current_rotation_state) != 1)
                    {
                        // didn't pass, try again
                        (current_piece->current_rotation_state)++;
                        continue;
                    }

                    // post-adding checks
                    if (run_all_checks(board, enable_slow_checks) != 1)
                    {
                        // remove the piece if the post-adding checks didn't pass, and try again
                        undo_last_piece_adding(board);
                        (current_piece->current_rotation_state)++;
                        continue;
                    }

                    // All checks passed
                    // New valid board found !

                    update_piece_all_drawing(current_piece, false, false);
                    valid_board_count++;
                    // get next piece to play
                    setup_next_piece();
                    return; // draw every frame that a new board is found
                }
                current_piece->current_rotation_state = 0;
                (current_piece->current_base_pos.j)++;
            }
            current_piece->current_base_pos.j = 0;
            (current_piece->current_base_pos.i)++;
        }
        current_piece->current_base_pos.i = 0;
        (current_piece->current_side_idx)++;
    }
    current_piece->current_side_idx = 0;

    // end of play possibilities for this piece, try to go to previous one (actual "backtrack")
    setup_previous_piece();
    goto algo_beginning;
}

void DrawSolverScreen(void)
{

    ClearBackground(BLACK);

    draw_board(board);

    // UI
    draw_piece_priority_array(piece_priority_array, piece_selected, nb_of_playable_pieces, playable_side_per_piece_idx_mask);
    draw_level_num(level_num_selected);
    draw_game_controls();
    draw_game_mode_choice();
    draw_separator();

    // ending message
    if (ending)
        draw_solver_result(successful_ending, total_time, valid_board_count);
}
void UnloadSolverScreen(void)
{
    free(board);
    free(level_hints);
}
int FinishSolverScreen(void) { return finishScreen; }

// --------------------------------------------------------------------------------------------------------------
// More helper functions for the algorithm
// --------------------------------------------------------------------------------------------------------------

static void setup_next_combination(void)
{
    combination_idx++;
    if (combination_idx >= start_combinations.nb_of_combinations)
    {
        // case where we have tested all possibilities
        // there's no solution
        ending = true;
        total_time = GetTime() - start_time;
        return;
    }
    load_combination_data(board, &start_combinations, combination_idx, piece_priority_array, &nb_of_playable_pieces, playable_side_per_piece_idx_mask);
    is_backtrack_iteration = false;
    piece_selected = -1;
    setup_next_piece();
}

static void setup_previous_piece(void)
{

    piece_selected--;
    if (piece_selected < 0)
        return;

    is_backtrack_iteration = true;
    piece_idx = piece_priority_array[piece_selected];
    current_piece = (board->piece_array) + piece_idx;
}

static void setup_next_piece(void)
{

    piece_selected++;
    if (piece_selected == nb_of_playable_pieces)
        return;

    piece_idx = piece_priority_array[piece_selected];
    current_piece = (board->piece_array) + piece_idx;
}

// --------------------------------------------------------------------------------------------------------------
// More helper functions about custom fps for algorithm's visualization and updating input events
// --------------------------------------------------------------------------------------------------------------

static void set_target_fps(void)
{
    manual_frame_unwind_mode = false;
    enable_slow_checks = true;
    switch (fps_choice)
    {

    case 0:
        target_fps = DEFAULT_FPS;
        manual_frame_unwind_mode = true;
        break;

    case 1:
        target_fps = 1;
        break;

    case 2:
        target_fps = 3;
        break;

    case 3:
        target_fps = 10;
        break;

    case 4:
        target_fps = 30;
        break;

    case 5:
        target_fps = 60;
        break;

    case 6:
        target_fps = 0;
        enable_slow_checks = false;
        break;

    default:
        break;
    }
}

static void update_inputs(void)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        finishScreen = 1;
        return;
    }

    fps_choice = draw_FPS_choice();
    if (fps_choice == previous_fps_choice)
        return;

    previous_fps_choice = fps_choice;

    set_target_fps();

    if (target_fps == 0)
    {
        SetTargetFPS(0);
        frame_update_frequency = 1; // update at every frame
    }
    else
    {
        SetTargetFPS(DEFAULT_FPS);
        frame_update_frequency = (int)(DEFAULT_FPS / target_fps);
        // example with DEFAULT_FPS = 60 | target_fps = 10
        // we want to update 1 frame out of 6
        // thus allow updating when frame_count % 6 == 0
    }
}