/**
 * @file test_display.c
 * Unit testing on display.c api
 *
 * @warning This file currently only includes visual testing
 * This is not really a proper "unit testing" file where tests are automated with assertions
 */

#include <local/piece.h>
#include <local/check_board.h>
#include <local/display.h>
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

Board *setup_board_with_level_hints(LevelHints *level_hints, bool show_border_tiles)
{
    Board *board = init_board(level_hints);
    update_board_grid_drawing(board);
    update_board_obligatory_tiles_drawing(board);

    for (int i = 0; i < board->nb_of_added_pieces; i++)
        update_piece_all_drawing((board->piece_array) + board->added_piece_idx_array[i], show_border_tiles);

    return board;
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

void print_check_result(int return_result)
{
    printf("\nCurrently running post-adding checks...\n");
    if (return_result == ISOLATED_EMPTY_TILE)
    {
        printf("1) Error : Adding this piece creates an isolated empty tile, which can't be filled anymore.\n");
        return;
    }
    printf("1) OK    : No isolated empty tile created.\n");

    if (return_result == DEAD_END)
    {
        printf("2) Error : Adding this piece creates a dead end, certain tiles can't be linked by a path anymore.\n");
        return;
    }
    printf("2) OK    : No dead end created.\n");
    if (return_result == LOOP_PATH)
    {
        printf("3) Error : Adding this piece creates a loop path, which is not allowed by game rules.\n");
        return;
    }
    printf("3) OK    : No loop path created.\n");

    printf("All checks passed !\n\n");
}

void print_controls(void)
{

    printf("Controls :\n\n");
    printf("\t- left/right arrow keys : change current level /!\\ everything will be reset if level is changed\n");
    printf("\n");
    printf("\t- ZQSD(or WASD)         : move the piece accross the board (up, left, down, right respectively)\n");
    printf("\t- spacebar              : change piece selected\n");
    printf("\t- F                     : change side displayed of current piece\n");
    printf("\t- R                     : rotate the piece clockwise\n");
    printf("\n");
    printf("\t- Enter                 :  Try to add current piece to the board in its current state\n");
    printf("\t                           Displays various comments when the piece can't be added\n");
    printf("\t- E                     : Undo last piece adding from the board\n");
    printf("\n");
    printf("\t- T                     : toggle tile pos display (i, j) on each tile\n");
    printf("\n\n");
}

char *board_interactive_display_test()
{
    /*
    To display the result of the encoding of game board adding and removing pieces + level hints
    It is basically an IQ circuit game simulator now, where we can play levels 49 to 120 included
    Controls :

        - left/right arrow keys : change current level /!\ everything will be reset if level is changed

        - spacebar : change piece selected
        - F : change side displayed of current piece
        - R : rotate the piece clockwise

        - ZQSD (or WASD) : move the piece accross the board (up,left,down,right respectively)

        - Enter : Try to add current piece to the board in its current state
            Displays various comments when the piece can't be added, see "print_adding_result" function and board.c > "can_piece_be_added_to_board"

        - E : Undo last piece adding from the board

        - (T : toggle tile pos(i,j) display)
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

    setup_display();

    int control_keys[] = {KEY_W, KEY_A, KEY_S, KEY_D, KEY_R, KEY_F, KEY_SPACE, KEY_ENTER, KEY_RIGHT, KEY_LEFT}; // KEY_E is intentionally kept out from this list
    int nb_of_keys = 10;

    // Setup of variables and parameters

    // constants
    bool show_missing_connection_tiles = false;
    bool show_border_tiles = false;

    // main data variables
    int level_num = 85;
    LevelHints *level_hints = get_level_hints(level_num);
    Board *board = setup_board_with_level_hints(level_hints, show_border_tiles);
    int nb_of_level_pieces = board->nb_of_added_pieces;

    // input variables
    int piece_idx = -1;
    int side_idx = 0;
    int rotation_state = 0;
    Vector2_int base_pos = {0, 0};

    // state of the game variables
    char level_num_str[4];
    bool display_tile_pos = false;
    bool try_adding_piece = false;
    bool need_level_reset = false;
    bool board_complete = false;
    int return_val;

    // initialize piece first state and first level
    sprintf(level_num_str, "%d", level_num);
    piece_idx = get_next_piece_idx(board, piece_idx); // to account for already played pieces (obligatory pieces from level hints)
    Piece *piece = (board->piece_array) + piece_idx;

    blit_piece_main_data(piece, side_idx, base_pos, rotation_state);
    update_piece_all_drawing(piece, show_border_tiles);
    // print_controls();
    print_piece_pos_infos(piece);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_T))
            display_tile_pos = !display_tile_pos;

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
            piece = (board->piece_array) + piece_idx;
            side_idx = 0;
        }

        if (IsKeyPressed(KEY_E))
        {
            system("cls");
            // print_controls();
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

        if (IsKeyPressed(KEY_RIGHT) && level_num < 120)
        {
            need_level_reset = true;
            level_num++;
        }
        if (IsKeyPressed(KEY_LEFT) && level_num > 49)
        {
            need_level_reset = true;
            level_num--;
        }

        if (need_level_reset)
        {
            need_level_reset = false;
            try_adding_piece = false;
            free(level_hints);
            free_board(board);

            sprintf(level_num_str, "%d", level_num);

            level_hints = get_level_hints(level_num);
            board = setup_board_with_level_hints(level_hints, show_border_tiles);
            nb_of_level_pieces = board->nb_of_added_pieces;

            // to account for already played pieces (obligatory pieces from level hints)
            piece_idx = -1;
            piece_idx = get_next_piece_idx(board, piece_idx);
            piece = (board->piece_array) + piece_idx;
            side_idx = 0;
        }

        if (IfAnyIsPressedKey(control_keys, nb_of_keys))
        {

            if (!try_adding_piece)
            {
                blit_piece_main_data(piece, side_idx, base_pos, rotation_state);
                system("cls");
                // print_controls();
                print_piece_pos_infos(piece);
            }
            else
            {
                system("cls");
                // print_controls();
                print_piece_pos_infos(piece);
                printf("\nCurrently trying to add the piece to the board...\n");
                return_val = add_piece_to_board(board, piece_idx, side_idx, base_pos, rotation_state);
                print_adding_result(return_val);

                if (return_val == 1)
                {

                    return_val = run_all_checks(board);
                    print_check_result(return_val);

                    if (return_val != 1)
                    {
                        printf("Currently removing last added piece to the board as it will not lead to a complete board with previous played piece.\n");
                        undo_last_piece_adding(board);
                    }
                    else
                    {
                        update_piece_all_drawing(piece, show_border_tiles);
                        // move on to next piece automatically only if adding and checks all passed
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
        draw_level_num(level_num_str);
        if (display_tile_pos)
            draw_pos_text();
        EndDrawing();
    }

    CloseWindow();
    free_board(board);
    free(level_hints);
    if (board_complete)
    {
        system("cls");
        // print_controls();
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