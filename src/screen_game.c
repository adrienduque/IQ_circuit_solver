/**
 * @author Adrien Duqué (@adrienduque)
 * Original Github repository : https://github.com/adrienduque/IQ_circuit_solver
 *
 * @file screen_level_select.c
 * @see screens.h
 *
 * File containing Update and Draw functions for the user playable mode of a game level, see screens.h and raylib game templates
 */
#include <stdbool.h>
#include <stdlib.h> // NULL

#include <raylib/raylib.h>
#include <raylib/raygui.h>

#include <raylib/screens.h>

#include <local/board.h> // Board
#include <local/level_data.h>
#include <local/piece.h>
#include <local/check_board.h> // run_all_checks
#include <local/display.h>
#include <local/utils.h> // assets_folder_relative_path

typedef enum GameMode
{
    FREE = 0,
    ASSISTED,

} GameMode;

typedef struct Controls
{
    int piece_idx, side_idx, rotation_state;
    Vector2_int base_pos;
    bool remove_piece_this_frame;
    bool add_piece_this_frame;

} Controls;

static void reset_controls();
static void set_controls(int piece_idx);
static void update_controls();

static void update_current_piece();

static bool is_piece_idx_already_played(int piece_idx);
static int get_next_piece_idx(int piece_idx);

static Board *board;
static LevelHints *level_hints;
static Piece *current_piece;
static Controls controls;

static GameMode game_mode, previous_game_mode;

static int error_status;
static bool are_all_pieces_played;

static int finishScreen;

void InitGameScreen(void)
{
    level_hints = get_level_hints(level_num_selected);
    board = init_board(level_hints);
    update_board_static_drawing(board);

    reset_controls();

    game_mode = draw_game_mode_choice();
    previous_game_mode = game_mode;

    error_status = IDLE; // Waiting for user to add a piece
    are_all_pieces_played = false;

    finishScreen = 0;
}

void UpdateGameScreen(void)
{
    static int next_piece_idx;

    // Screen switching logic
    if (draw_launch_button())
    {
        finishScreen = 1;
        return;
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        finishScreen = -1; // go back to previous screen, see main.c
        return;
    }

    update_controls();

    game_mode = draw_game_mode_choice();

    // Reset everything when switching modes
    if (game_mode != previous_game_mode)
    {
        UnloadGameScreen();
        InitGameScreen();
        return;
    }

    // undo logic
    if (controls.remove_piece_this_frame)
    {
        controls.remove_piece_this_frame = false;

        if (board->nb_of_added_pieces <= board->nb_of_level_pieces)
            error_status = UNDO_ERROR; // error : there is no piece to remove (or these are part of level hints)

        else
        {
            // different undo methods for the different game modes
            if (game_mode == ASSISTED)
                undo_last_piece_adding(board);
            else
                board->nb_of_added_pieces--;

            // undo blocking end flag, we can add piece again
            if (are_all_pieces_played)
            {
                are_all_pieces_played = false;
                reset_controls();
            }

            error_status = UNDO_SUCCESS; // Successfully removed piece
        }

        return;
    }

    // can't add more pieces if they already all have been played
    if (are_all_pieces_played)
        return;

    // add logic in 2 different game modes
    if (controls.add_piece_this_frame)
    {
        controls.add_piece_this_frame = false;

        switch (game_mode)
        {

        case FREE:

            board->added_piece_idx_array[board->nb_of_added_pieces] = controls.piece_idx;
            board->nb_of_added_pieces++;

            error_status = ADD_SUCCESS;

            // check if all pieces have been played while trying to get the next playable piece index
            next_piece_idx = get_next_piece_idx(controls.piece_idx);
            if (next_piece_idx == -1)
            {
                // board maybe completed, we just know that all piece have been played in this case
                current_piece = NULL;
                are_all_pieces_played = true;
                error_status = ALL_PIECE_PLAYED;
                return;
            }
            // if all the pieces have not been played, update next piece
            set_controls(next_piece_idx);
            break;

        case ASSISTED:

            // Try adding the piece to the board with actual board pre-adding and post-adding checks, see board.c and check_board.c

            // pre-adding checks
            error_status = add_piece_to_board(board, controls.piece_idx, controls.side_idx, controls.base_pos, controls.rotation_state);

            if (error_status != ADD_SUCCESS)
                return;

            // case where it has been successfully added, but is the board still worth continuing ? -> post-adding checks
            error_status = run_all_checks(board, true);

            if (error_status != ADD_SUCCESS)
            {
                // Answer : no, so remove the piece from the board
                undo_last_piece_adding(board);
                error_status += 10; // see display.c > draw_board_validation
                return;
            }

            // Answer : Yes, it has been successfully added (error_status == ADD_SUCCESS here)
            // check if all pieces have been played while trying to get the next playable piece index
            next_piece_idx = get_next_piece_idx(controls.piece_idx);

            if (next_piece_idx == -1)
            {
                // In this case, we know that all piece have been played
                // But it means that the last piece have been added without errors
                // So the board is currently solved !
                current_piece = NULL;
                are_all_pieces_played = true;
                error_status = BOARD_COMPLETED;
                return;
            }

            // if the board is not completed yet, update next piece
            set_controls(next_piece_idx);
            break;

        default:
            break;
        }
    }
}

void DrawGameScreen(void)
{
    ClearBackground(BLACK);

    draw_board(board);

    if (current_piece != NULL)
        draw_piece(current_piece, false, false);

    // UI
    draw_level_num(level_num_selected);
    draw_game_controls();
    draw_separator();
    draw_FPS_choice();
    draw_board_validation(error_status);
}

void UnloadGameScreen(void)
{

    free(board);
    free(level_hints);
}

int FinishGameScreen(void) { return finishScreen; }

// --------------------------------------------------------------------------------------------------------------
// More helper functions
// --------------------------------------------------------------------------------------------------------------

// Used in get_next_piece_idx
static bool is_piece_idx_already_played(int piece_idx)
{

    for (int i = 0; i < board->nb_of_added_pieces; i++)
    {
        if (board->added_piece_idx_array[i] == piece_idx)
            return true;
    }
    return false;
}

// Function to get the next playable piece index among the remaining playable pieces
// playable := the piece is not on the board yet
// return -1 if all the piece have been played
static int get_next_piece_idx(int piece_idx)
{
    if (board->nb_of_added_pieces == 10)
        return -1;
    do
    {
        piece_idx = (piece_idx + 1) % NB_OF_PIECES;
    } while (is_piece_idx_already_played(piece_idx));

    return piece_idx;
}

static void set_controls(int piece_idx)
{
    controls = (Controls){.side_idx = 0, .rotation_state = 0, .base_pos = (Vector2_int){-2, -2}, .add_piece_this_frame = false, .remove_piece_this_frame = false};

    controls.piece_idx = (piece_idx != -1) ? piece_idx : get_next_piece_idx(piece_idx); // to account for piece already played, the starting index is dynamically set with piece_idx=-1 and searching for next valid piece_idx

    update_current_piece();
}

static void reset_controls(void)
{
    set_controls(-1);
}

static void update_controls(void)
{

    if (IsKeyPressed(KEY_E))
        controls.remove_piece_this_frame = true;

    if (are_all_pieces_played)
        // disable further controls if all the piece have been played (current_piece == NULL here too)
        return;

    if (IsKeyPressed(KEY_W))
        increment_pos_in_direction(&(controls.base_pos), UP);

    if (IsKeyPressed(KEY_A))
        increment_pos_in_direction(&(controls.base_pos), LEFT);

    if (IsKeyPressed(KEY_S))
        increment_pos_in_direction(&(controls.base_pos), DOWN);

    if (IsKeyPressed(KEY_D))
        increment_pos_in_direction(&(controls.base_pos), RIGHT);

    if (IsKeyPressed(KEY_F))
        controls.side_idx = (controls.side_idx + 1) % (current_piece->nb_of_sides);

    if (IsKeyPressed(KEY_R))
        controls.rotation_state = (controls.rotation_state + 1) % NB_OF_DIRECTIONS;

    if (IsKeyPressed(KEY_C))
    {
        controls.piece_idx = get_next_piece_idx(controls.piece_idx);
        controls.side_idx = 0;
    }

    if (IsKeyPressed(KEY_SPACE))
        controls.add_piece_this_frame = true;

    update_current_piece();
}

static void update_current_piece(void)
{
    current_piece = (board->piece_array) + controls.piece_idx;
    blit_piece_main_data(current_piece, controls.side_idx, controls.base_pos, controls.rotation_state);
    update_piece_all_drawing(current_piece, false, false);
}