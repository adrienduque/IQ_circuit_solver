/**
 * @file test_display.c
 * Unit testing on display.c api
 *
 * @warning This file currently only includes visual testing
 * This is not really a proper "unit testing" file where tests are automated with assertions
 */

#include <local/display.h>
#include <local/piece.h>
#include <minunit.h>
#include <stdio.h>
#include <stdlib.h>

int tests_run = 0;

// function used in piece_data_display_test()
static void print_piece_pos_infos(Piece *piece)
{
    printf("Piece : %s | side %d at (pos : {%d,%d} | rota : %d) \n", piece->name, piece->current_side_idx, piece->current_base_pos.i, piece->current_base_pos.j, piece->current_rotation_state);
}

// helper function for piece_data_display_test
bool IfAnyIsPressedKey(int *KeyArray, int nb_of_keys)
{

    int Key;
    for (int i = 0; i < nb_of_keys; i++)
    {
        Key = KeyArray[i];
        if (IsKeyPressed(Key))
            return true;
    }
    return false;
}

char *piece_data_display_test()
{
    /*
    To display the result of the encoding of game pieces on the board
    And to showcase how the visualization of the main algorithm will look like
    Controls :
        - spacebar : change piece displayed
        - F : change side displayed of current piece
        - R : rotate the piece clockwise

        - ZQSD (or WASD) : move the piece accross the board (up,left,down,right respectively)

        - C : to toggle drawing of missing connection tiles
        - B : to toggle drawing of border tiles

    See : "showcase assets"/"test_display first example.png" to see what the output looks like

    */

    Piece *piece_array = get_piece_array();

    int control_keys[] = {KEY_W, KEY_A, KEY_S, KEY_D, KEY_R, KEY_F, KEY_SPACE, KEY_C, KEY_B};
    int nb_of_keys = 9;

    setup_display();

    // Initial state displayed and input parameters
    int piece_idx = 0;
    int side_idx = 0;
    Vector2_int base_pos = {1, 2}; // to start near the middle of the board
    int rotation_state = 0;
    bool show_missing_connection_tiles = true;
    bool show_border_tiles = true;

    // piece main live data holder
    Piece *piece = piece_array + piece_idx;

    // initialize piece first state
    blit_piece_main_data(piece, side_idx, base_pos, rotation_state);
    update_piece_border_tiles(piece);
    update_piece_all_drawing(piece, show_border_tiles);

    printf("Now entering interactive piece display test.\n\n");
    print_piece_pos_infos(piece);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_W))
            increment_pos_in_direction(&base_pos, UP);
        if (IsKeyPressed(KEY_A))
            increment_pos_in_direction(&base_pos, LEFT);
        if (IsKeyPressed(KEY_S))
            increment_pos_in_direction(&base_pos, DOWN);
        if (IsKeyPressed(KEY_D))
            increment_pos_in_direction(&base_pos, RIGHT);

        if (IsKeyPressed(KEY_R))
        {
            rotation_state += 1;
            rotation_state %= NB_OF_DIRECTIONS;
        }

        if (IsKeyPressed(KEY_F))
        {
            side_idx += 1;
            side_idx %= piece->nb_of_sides;
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            piece_idx += 1;
            piece_idx %= NB_OF_PIECES;
            piece = piece_array + piece_idx;
            side_idx = 0;
        }

        if (IsKeyPressed(KEY_C))
            show_missing_connection_tiles = !show_missing_connection_tiles;

        if (IsKeyPressed(KEY_B))
            show_border_tiles = !show_border_tiles;

        if (IfAnyIsPressedKey(control_keys, nb_of_keys))
        {
            // Update all cache live data even the unnecessary ones to simplify debug mode
            blit_piece_main_data(piece, side_idx, base_pos, rotation_state);
            update_piece_border_tiles(piece);
            update_piece_all_drawing(piece, show_border_tiles);

            system("cls");
            print_piece_pos_infos(piece);
        }

        // Always draw cached data
        BeginDrawing();
        ClearBackground(BLACK);
        draw_grid();
        draw_piece(piece, show_missing_connection_tiles, show_border_tiles);
        EndDrawing();
    }
    CloseWindow();
    free(piece_array);

    return 0;
}

int add_piece_to_board_with_draw_data(Board *board, int piece_idx, int side_idx, Vector2_int base_pos, int rotation_state)
{
    int return_val;
    return_val = add_piece_to_board(board, piece_idx, side_idx, base_pos, rotation_state);
    update_piece_all_drawing(board->piece_array + piece_idx, false);

    return return_val;
}

bool is_piece_idx_already_played(Board *board, int piece_idx)
{

    for (int i = 0; i < board->nb_of_added_pieces; i++)
    {
        if (board->added_piece_idx_array[i] == piece_idx)
            return true;
    }
    return false;
}

int get_next_piece_idx(Board *board, int piece_idx)
{
    if (board->nb_of_added_pieces == 10)
        return -1;
    do
    {
        piece_idx += 1;
        piece_idx %= NB_OF_PIECES;
    } while (is_piece_idx_already_played(board, piece_idx));

    return piece_idx;
}

void print_adding_result(int return_val)
{

    switch (return_val)
    {
    case 1:
        printf("Success !\n");
        break;

    case -1:
        printf("Error : One or more tiles are out of bounds ! (or missing connection tiles which are not drawn) \n");
        break;

    case -2:
        printf("Error : One or more tiles are superposed !\n");
        break;

    case -3:
        printf("Error : Connections are not right !\n");
        break;

    case -4:
        printf("Error : One or more tiles don't match level hints !\n");
        break;

    case -5:
        printf("Error : A tile is expecting 3 connections at a time, not allowed\n");
        break;

    case -6:
        printf("Error : A tile is expecting 2 connections at a time, but can't be filled with current playable remaining pieces\n");
        break;

    default:
        break;
    }
}

char *board_interactive_display_test()
{
    /*
    To display the result of the encoding of game board adding and removing pieces
    Controls :
        - spacebar : change piece selected
        - F : change side displayed of current piece
        - R : rotate the piece clockwise

        - ZQSD (or WASD) : move the piece accross the board (up,left,down,right respectively)

        - Enter : Try to add current piece to the board in its current state
            Displays various comments when the piece can't be added, see "print_adding_result" function and board.c > "can_piece_be_added_to_board"

        - E : Undo last piece adding from the board

        - (P : pause exécution in debugger mode (by going to a breakpoint line))

    */

    /*
    Results so far :
    I feel like everything is working as expected, even without going into debug mode to see the inner values
    I'll go into it nonetheless and see if I can spot a bug manually
        -> It seems ok, further unit testing might be needed if it goes wrong later, but for now, not priority
     */
    system("cls");
    printf("Now entering interactive board display test.\n\n");

    int control_keys[] = {KEY_W, KEY_A, KEY_S, KEY_D, KEY_R, KEY_F, KEY_SPACE, KEY_ENTER}; // KEY_E is intentionally kept out from this list
    int nb_of_keys = 8;

    // Setup of variables and parameters
    LevelHints *level_hints = get_level_hints(83); // test level is number 83
    Board *board = init_board(level_hints);

    bool show_missing_connection_tiles = false;
    bool show_border_tiles = false;

    int piece_idx = -1;
    int side_idx = 0;
    int rotation_state = 0;
    Vector2_int base_pos = {0, 0};

    setup_display();

    update_board_grid_drawing(board);
    update_board_obligatory_tiles_drawing(board);

    for (int i = 0; i < board->nb_of_added_pieces; i++)
        update_piece_all_drawing((board->piece_array) + board->added_piece_idx_array[i], show_border_tiles);

    bool try_adding_piece = false;
    bool board_complete = false;
    int nb_of_level_pieces = board->nb_of_added_pieces;
    int return_val;

    piece_idx = get_next_piece_idx(board, piece_idx); // to account for already played pieces (obligatory pieces from level hints)
    Piece *piece = (board->piece_array) + piece_idx;

    // initialize piece first state
    blit_piece_main_data(piece, side_idx, base_pos, rotation_state);
    update_piece_all_drawing(piece, show_border_tiles);
    print_piece_pos_infos(piece);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_W))
            increment_pos_in_direction(&base_pos, UP);
        if (IsKeyPressed(KEY_A))
            increment_pos_in_direction(&base_pos, LEFT);
        if (IsKeyPressed(KEY_S))
            increment_pos_in_direction(&base_pos, DOWN);
        if (IsKeyPressed(KEY_D))
            increment_pos_in_direction(&base_pos, RIGHT);

        if (IsKeyPressed(KEY_R))
        {
            rotation_state += 1;
            rotation_state %= NB_OF_DIRECTIONS;
        }

        if (IsKeyPressed(KEY_F))
        {
            side_idx += 1;
            side_idx %= piece->nb_of_sides;
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            piece_idx = get_next_piece_idx(board, piece_idx);
            if (piece_idx == -1)
            {
                board_complete = true;
                break;
            }
            piece = (board->piece_array) + piece_idx;
            side_idx = 0;
        }

        if (IsKeyPressed(KEY_E))
        {
            system("cls");
            printf("Currently trying to remove the last piece added to the board...\n");
            if (board->nb_of_added_pieces > nb_of_level_pieces)
            {
                undo_last_piece_adding(board);
                printf("Success !\n");
            }
            else
                printf("Error : There is no piece left to remove. (can't remove those that come from level hints)\n");
        }

        if (IsKeyPressed(KEY_ENTER))
            try_adding_piece = true;

        if (IfAnyIsPressedKey(control_keys, nb_of_keys))
        {

            if (!try_adding_piece)
            {
                blit_piece_main_data(piece, side_idx, base_pos, rotation_state);
                system("cls");
                print_piece_pos_infos(piece);
            }
            else
            {
                system("cls");
                print_piece_pos_infos(piece);
                printf("Currently trying to add the piece to the board...\n");
                return_val = add_piece_to_board(board, piece_idx, side_idx, base_pos, rotation_state);
                print_adding_result(return_val);

                if (return_val == 1)
                {
                    update_piece_all_drawing(piece, show_border_tiles);

                    // move on to next piece automatically
                    piece_idx = get_next_piece_idx(board, piece_idx);
                    if (piece_idx == -1)
                    {
                        board_complete = true;
                        break;
                    }
                    piece = (board->piece_array) + piece_idx;
                    side_idx = 0;
                    base_pos.i = 0;
                    base_pos.j = 0;
                    rotation_state = 0;
                    blit_piece_main_data(piece, side_idx, base_pos, rotation_state);
                }

                try_adding_piece = false;
            }

            update_piece_all_drawing(piece, show_border_tiles);
        }
        if (IsKeyPressed(KEY_P))
            printf("pause breakpoint.\n");

        BeginDrawing();
        ClearBackground(BLACK);
        draw_board(board, show_missing_connection_tiles);
        draw_piece(piece, show_missing_connection_tiles, show_border_tiles);
        EndDrawing();
    }

    CloseWindow();
    free_board(board);
    free(level_hints);
    if (board_complete)
    {
        system("cls");
        printf("Board complete ! Stopping display test.\n");
    }
    return 0;
}

char *all_tests()
{
    // mu_run_test(piece_data_display_test);
    mu_run_test(board_interactive_display_test);
    return 0;
}

int main(void)
{
    printf("Press any key to continue testing.\n");
    getchar();
    system("cls");
    char *test_results = all_tests();
    if (test_results != 0)
        printf("Error. Test failed. Msg : %s\n", test_results);
    else
        printf("All tests passed! (%d total tests)\n", tests_run);

    return 0;
}