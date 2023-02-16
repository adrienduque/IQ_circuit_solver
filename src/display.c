/**
 * @file display.c
 *
 * File containing all graphic display functions used for the main algorithm visualization and debugging
 * Based on the raylib API
 *
 * @warning pixel display is basically mapped to 2D indexing of tiles by : (px,py) = (i,j) * tile_px_width
 * @see utils.h and utils.c
 * And there is an offset to this 2D coordinates to draw the board in the center of the window
 *
 * The same idea of caching is used for drawing data
 * At each different main data drawing section there is :
 * 1) Function to compute cache drawing data, used only when they need to be updated, thus called once in a while (e.g : piece moving on the board -> time to update its drawing)
 * 2) Function to effectively draw the cached data (which is called in repeat, in classic drawing loops)
 *
 */

#include <stdbool.h>
#include <stdio.h>  // sprintf
#include <stdlib.h> // NULL

#define RAYGUI_IMPLEMENTATION
#include <raylib/raygui.h>
#include <raylib/raylib.h> // Color, primary drawing functions, and defines

#include <local/utils.h>       // Vector2_int, Directoin, helper functions, and defines
#include <local/piece_data.h>  // Tile, Side, Piece, and defines
#include <local/piece.h>       // blit_piece_main_data
#include <local/board.h>       // Board, and defines
#include <local/check_board.h> // defines

#include <local/display.h>

// -----------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------- Drawing constants ------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------

//---- Main global constant parameters ------------------------------------------

Vector2_int offset_px;
static int offset_y_level_num;
static Color connection_line_color = {212, 175, 55, 255};
static Color outline_color = {200, 255, 0, 255};

const int gui_icon_scale = 3;

const int tile_px_width = 101;
static const int small_tile_px_width = 31;

// Driven parameters
static const int grid_line_px_thick = tile_px_width / 10;
static const int connection_line_px_thick = tile_px_width / 10;
static const int outline_px_thick = (int)(tile_px_width * 0.08);
static const float bend_circle_radius = (float)(connection_line_px_thick / 2 - 1);
static const float point_circle_radius = (float)(tile_px_width / 6);

// values to add from center x,y, to get the other point of the line (tip) to draw the connection in the right direction
// see update_tile_drawing when it treats connection lines
static Vector2_int connections_tip_offset[] = {
    [RIGHT] = {tile_px_width / 2, 0},
    [DOWN] = {0, tile_px_width / 2},
    [LEFT] = {-tile_px_width / 2, 0},
    [UP] = {0, -tile_px_width / 2},
};

// small version of the same constants, see  "draw_piece_priority_array" function

static const int small_connection_line_px_thick = small_tile_px_width / 10;
static const int small_outline_px_thick = (int)(small_tile_px_width * 0.08);
static const float small_bend_circle_radius = (float)(small_connection_line_px_thick / 2 - 1);
static const float small_point_circle_radius = (float)(small_tile_px_width / 6);

static Vector2_int small_connections_tip_offset[] = {
    [RIGHT] = {small_tile_px_width / 2, 0},
    [DOWN] = {0, small_tile_px_width / 2},
    [LEFT] = {-small_tile_px_width / 2, 0},
    [UP] = {0, -small_tile_px_width / 2},
};

//---- parameter used in functions --------------------------------------------------------------------

static int current_tile_px_width;

static int current_connection_line_px_thick;
static int current_outline_px_thick;
static float current_bend_circle_radius;
static float current_point_circle_radius;

static Vector2_int *current_connections_tip_offset;

// -----------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------- Manually extending raylib -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------

// Function to initialize a raylib window
void setup_display(int window_px_width, int window_px_height)
{
    // global variables setup
    current_tile_px_width = tile_px_width;
    current_connection_line_px_thick = connection_line_px_thick;
    current_outline_px_thick = outline_px_thick;
    current_bend_circle_radius = bend_circle_radius;
    current_point_circle_radius = point_circle_radius;
    current_connections_tip_offset = connections_tip_offset;

    // we have to figure out the offset for the board to display in the center of the screen height
    int half_board_px_height = (int)(BOARD_HEIGHT * tile_px_width / 2);
    int center_px_y = (int)(window_px_height / 2);

    offset_px.i = 3 * tile_px_width;
    offset_px.j = center_px_y - half_board_px_height;

    offset_y_level_num = offset_px.j - 60;

    // actual initialization of the display
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN | FLAG_WINDOW_TOPMOST);
    SetTraceLogLevel(LOG_ERROR);

    InitWindow(window_px_width, window_px_height, "Raylib Board Visualization");
    SetExitKey(KEY_NULL);

    // Gui Initialisation
    GuiSetIconScale(gui_icon_scale);

    GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, 0x838383ff);
    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, 0x000000ff);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0x686868ff);

    GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, 0xffa100ff);
    GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, 0x000000ff);
    GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, 0xffa100ff);

    GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, 0xd48602ff);
    GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, 0x000000ff);
    GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, 0xd48602ff);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

#ifdef USE_SECOND_SCREEN
    // Quality of life for debugging
    // Hack that only works for my particular setup :
    // main screen : laptop 1080p (but scaled to 125% (default Windows parameter))
    // Second screen : to the left, 1080p, but scaled to 100% in Windows parameter

    // SetWindowMonitor(1); -> goes to my second screen, but fullscreen is mandatory with this function, and is not what I want

    // hack go to my second screen to the left, without going fullscreen
    SetWindowPosition(-1920 + 50, 50);

    // the difference in scaling between the 2 screen mess up the window size, this is to restore it
    SetWindowSize(window_px_width, window_px_height);

#endif
}

// Function to add on top of raylib library : DrawLineStrip function but with a thickness option
static void DrawLineStripEx(Vector2 *points, int pointCount, float thick, Color color)
{
    for (int i = 0; i < pointCount - 1; i++)
        DrawLineEx(points[i], points[i + 1], thick, color);
}

// -----------------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------Main elementary drawing sub functions ------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------- Functions to draw the background grid of the game board -----------------------------------------------------------

/**
 * @warning depreciated function still used in test_display.c, new function -> update_board_grid_drawing + draw_board_grid
 */
void draw_grid()
{
    float pt_x, pt_y, pt1_y, pt2_y, pt1_x, pt2_x;
    Vector2 start_point, end_point;
    for (int idx = 0; idx < BOARD_WIDTH + 1; idx++)
    {
        pt_x = (idx * tile_px_width + offset_px.i);
        pt1_y = offset_px.j;
        pt2_y = (BOARD_HEIGHT * tile_px_width) + offset_px.j;
        start_point.x = pt_x;
        start_point.y = pt1_y;
        end_point.x = pt_x;
        end_point.y = pt2_y;

        DrawLineEx(start_point, end_point, grid_line_px_thick, GRAY);
    }
    for (int idx = 0; idx < BOARD_HEIGHT + 1; idx++)
    {
        pt_y = (idx * tile_px_width) + offset_px.j;
        pt1_x = offset_px.i;
        pt2_x = (BOARD_WIDTH * tile_px_width) + offset_px.i;
        start_point.x = pt1_x;
        start_point.y = pt_y;
        end_point.x = pt2_x;
        end_point.y = pt_y;

        DrawLineEx(start_point, end_point, grid_line_px_thick, GRAY);
    }
}

static void update_board_grid_drawing(Board *board)
{
    float pt_x, pt_y, pt1_y, pt2_y, pt1_x, pt2_x;
    int current_point_couple_idx = 0;
    for (int idx = 0; idx < BOARD_WIDTH + 1; idx++)
    {
        pt_x = (idx * tile_px_width + offset_px.i);
        pt1_y = offset_px.j;
        pt2_y = (BOARD_HEIGHT * tile_px_width) + offset_px.j;

        board->grid_lines_pt_array[current_point_couple_idx][0].x = pt_x;
        board->grid_lines_pt_array[current_point_couple_idx][0].y = pt1_y;
        board->grid_lines_pt_array[current_point_couple_idx][1].x = pt_x;
        board->grid_lines_pt_array[current_point_couple_idx][1].y = pt2_y;

        current_point_couple_idx++;
    }
    for (int idx = 0; idx < BOARD_HEIGHT + 1; idx++)
    {
        pt_y = (idx * tile_px_width) + offset_px.j;
        pt1_x = offset_px.i;
        pt2_x = (BOARD_WIDTH * tile_px_width) + offset_px.i;

        board->grid_lines_pt_array[current_point_couple_idx][0].x = pt1_x;
        board->grid_lines_pt_array[current_point_couple_idx][0].y = pt_y;
        board->grid_lines_pt_array[current_point_couple_idx][1].x = pt2_x;
        board->grid_lines_pt_array[current_point_couple_idx][1].y = pt_y;

        current_point_couple_idx++;
    }
}

static void draw_board_grid(Board *board)
{
    static int i;
    for (i = 0; i < NB_OF_GRID_LINES; i++)
        DrawLineEx(board->grid_lines_pt_array[i][0], board->grid_lines_pt_array[i][1], grid_line_px_thick, GRAY);
}

// --------------------------- Functions to draw normal and missing_connection tiles  ------------------------------------------------------------

static void update_tile_drawing(Tile *tile)
{
    static int idx;
    static Direction connection_direction;

    tile->top_left_corner_pt.i = (tile->absolute_pos.i * current_tile_px_width) + offset_px.i;
    tile->top_left_corner_pt.j = (tile->absolute_pos.j * current_tile_px_width) + offset_px.j;

    tile->center_pt.x = tile->top_left_corner_pt.i + current_tile_px_width / 2;
    tile->center_pt.y = tile->top_left_corner_pt.j + current_tile_px_width / 2;

    for (idx = 0; idx < tile->nb_of_connections; idx++)
    {
        connection_direction = tile->connection_direction_array[idx];
        tile->connection_pt_array[idx].x = tile->center_pt.x + current_connections_tip_offset[connection_direction].i;
        tile->connection_pt_array[idx].y = tile->center_pt.y + current_connections_tip_offset[connection_direction].j;
    }
}

static void draw_tile_color(Tile *tile, Color connection_color)
{
    static int i;
    for (i = 0; i < tile->nb_of_connections; i++)
    {
        DrawLineEx(tile->center_pt, tile->connection_pt_array[i], current_connection_line_px_thick, connection_color);
    }

    if (tile->tile_type == bend)
    {
        DrawCircle((int)tile->center_pt.x, (int)tile->center_pt.y, current_bend_circle_radius, connection_color);
    }
    else if (tile->tile_type == point)
    {
        DrawCircle((int)tile->center_pt.x, (int)tile->center_pt.y, current_point_circle_radius, connection_color);
    }

    DrawRectangleLines(tile->top_left_corner_pt.i, tile->top_left_corner_pt.j, current_tile_px_width, current_tile_px_width, WHITE);
}

// shortcut to draw normal tiles with connection color : gold
// see draw_tile_color
static void draw_tile(Tile *tile)
{
    draw_tile_color(tile, connection_line_color);
}

// shortcut to draw missing connection tiles with connection color : red
// see draw_tile_color
// these are separate functions, because I might only use it to debug the data and not use it in the main visualization
static void draw_missing_connection_tile(Tile *tile)
{
    draw_tile_color(tile, RED);
}
// --------------------------- Functions to draw border tiles (used only in debugging, see test_display.c)  --------------------------------------------

static void update_piece_border_tiles_drawing(Piece *piece)
{

    for (int idx = 0; idx < piece->nb_of_border_tiles; idx++)
    {
        if (!is_pos_valid(&(piece->border_tile_absolute_pos_array[idx])))
        {
            set_invalid_pos(&(piece->border_tile_effective_absolute_top_left_corner_pt_array[idx]));
            continue;
        }
        piece->border_tile_effective_absolute_top_left_corner_pt_array[idx].i = (piece->border_tile_absolute_pos_array[idx].i * current_tile_px_width) + offset_px.i;
        piece->border_tile_effective_absolute_top_left_corner_pt_array[idx].j = (piece->border_tile_absolute_pos_array[idx].j * current_tile_px_width) + offset_px.j;
    }
}

void draw_piece_border_tiles(Piece *piece)
{
    static Rectangle rec;
    for (int idx = 0; idx < piece->nb_of_border_tiles; idx++)
    {
        if (!is_pos_valid(&(piece->border_tile_effective_absolute_top_left_corner_pt_array[idx])))
            continue;
        rec.x = (float)(piece->border_tile_effective_absolute_top_left_corner_pt_array[idx].i);
        rec.y = (float)(piece->border_tile_effective_absolute_top_left_corner_pt_array[idx].j);
        rec.width = (float)current_tile_px_width;
        rec.height = (float)current_tile_px_width;

        DrawRectangleLinesEx(rec, (float)current_outline_px_thick, SKYBLUE);
    }
}

// --------------------------- Functions to draw outline edge of pieces  -------------------------------------------------------------------------

static Vector2_int outline_edge_correction_values[] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};

// Function to blit only outline edge points of side at the right emplacement in the board for display
static void update_piece_outline_drawing(Piece *piece)
{
    static Side *side = NULL;
    static Vector2_int temp_pos;
    static int i;

    side = (piece->side_array) + (piece->current_side_idx);

    // why do the tile emplacements need a correction after the classic rotation / translation of relative positions ?
    // it's because the drawing function is assuming that when we pass her tile positions, we take the top-left corner of each to draw the outline edge of a piece
    // it will not remain true if we rotate the piece/side we want to draw.
    // for example : when we rotate 90° clockwise (: rotation_state=1), we want to take the top-right corner of each specified tile position (after classic placement computation)
    // so we take instead the top-left corner of their right neighbour (translation (1,0) for each position)

    for (i = 0; i < piece->nb_of_outline_tiles; i++)
    {
        // classic tile placement
        temp_pos = side->outline_tile_relative_pos_array[i];
        rotate_pos(&temp_pos, piece->current_rotation_state);
        translate_pos(&temp_pos, &(piece->current_base_pos));

        // take the right top-left corner according to the correction
        translate_pos(&temp_pos, &(outline_edge_correction_values[piece->current_rotation_state]));

        // Final data used in draw_piece_outline
        piece->outline_tile_effective_absolute_top_left_corner_pt_array[i].x = (temp_pos.i * current_tile_px_width) + offset_px.i;
        piece->outline_tile_effective_absolute_top_left_corner_pt_array[i].y = (temp_pos.j * current_tile_px_width) + offset_px.j;
    }
}

static void draw_piece_outline(Piece *piece)
{
    DrawLineStripEx(piece->outline_tile_effective_absolute_top_left_corner_pt_array, piece->nb_of_outline_tiles, current_outline_px_thick, outline_color);
}

// ---------------------------------------------------------------------------------------------------------------
// ---------------------------------- Convenience functions ------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------

static void update_tile_array_drawing(Tile *tile_array, int nb_of_tiles)
{
    static int i;
    for (i = 0; i < nb_of_tiles; i++)
        update_tile_drawing(tile_array + i);
}

static void draw_tile_array(Tile *tile_array, int nb_of_tiles)
{
    static int i;
    for (i = 0; i < nb_of_tiles; i++)
        draw_tile(tile_array + i);
}

static void draw_missing_connection_tile_array(Tile *tile_array, int nb_of_tiles)
{
    static int i;
    for (i = 0; i < nb_of_tiles; i++)
        draw_missing_connection_tile(tile_array + i);
}

// ----------------------

static void update_piece_tiles_drawing(Piece *piece, bool show_missing_connection_tiles)
{
    static Side *side = NULL;
    side = (piece->side_array) + piece->current_side_idx;

    update_tile_array_drawing(side->tile_array, side->nb_of_tiles);
    if (show_missing_connection_tiles)
        update_tile_array_drawing(side->missing_connection_tile_array, side->nb_of_missing_connection_tiles);
}

static void update_board_obligatory_tiles_drawing(Board *board)
{
    update_tile_array_drawing(board->obligatory_tile_array, board->nb_of_obligatory_tiles);
}

static void draw_piece_tiles(Piece *piece, bool show_missing_connection_tiles)
{
    static Side *side = NULL;
    side = (piece->side_array) + piece->current_side_idx;

    draw_tile_array(side->tile_array, side->nb_of_tiles);
    if (show_missing_connection_tiles)
        draw_missing_connection_tile_array(side->missing_connection_tile_array, side->nb_of_missing_connection_tiles);
}

// ----------------------

void update_piece_all_drawing(Piece *piece, bool show_missing_connection_tiles, bool show_border_tiles)
{
    update_piece_tiles_drawing(piece, show_missing_connection_tiles);
    update_piece_outline_drawing(piece);
    if (show_border_tiles)
        update_piece_border_tiles_drawing(piece);
}

void draw_piece(Piece *piece, bool show_missing_connection_tiles, bool show_border_tiles)
{

    draw_piece_tiles(piece, show_missing_connection_tiles);

    if (show_border_tiles)
        draw_piece_border_tiles(piece);

    draw_piece_outline(piece);
}

// ----------------------

void update_board_static_drawing(Board *board)
{
    update_board_grid_drawing(board);
    update_board_obligatory_tiles_drawing(board);

    for (int i = 0; i < board->nb_of_added_pieces; i++)
        update_piece_all_drawing((board->piece_array) + board->added_piece_idx_array[i], false, false);
}

void draw_board(Board *board)
{
    static int i;
    static int piece_idx;

    draw_board_grid(board);

    for (i = 0; i < board->nb_of_obligatory_tiles; i++)
        draw_tile_color((board->obligatory_tile_array + i), GRAY);

    for (i = 0; i < board->nb_of_added_pieces; i++)
    {
        piece_idx = board->added_piece_idx_array[i];
        draw_piece((board->piece_array) + piece_idx, false, false);
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------
// -------------------------- More interface displayed --------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------

void draw_level_num(int level_num)
{
    static char level_num_str[4];
    static int previous_level_num = -1;

    if (level_num != previous_level_num)
    {
        sprintf(level_num_str, "%d", level_num);
        previous_level_num = level_num;
    }
    DrawText(level_num_str, offset_px.i, offset_y_level_num, 50, ORANGE);
}

// function used to draw all tile poses on the window
// to help me when I'm debugging post-adding check methods in test_display.c
void draw_pos_text(void)
{
    static int corner_offset = 10;

    static int x;
    static int y;
    static char temp_text[4];

    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            sprintf(temp_text, "%d;%d", i, j);
            x = i * tile_px_width + offset_px.i + corner_offset;
            y = j * tile_px_width + offset_px.j + corner_offset;
            DrawText(temp_text, x, y, 20, WHITE);
        }
    }
}

// Function to draw the current piece priority array, aslo with the remaining pieces to play
// This is mainly to visualize when solver algorithm switch between different combinations
// The idea is to have a column of piece thumbnails next to the board display
// And fill it from the bottom up with the current priority array, and the other one with the remaining pieces to play in the array
// The first pieces in the priority list are at the top, and they are taken out 1 by 1 of the remaining list to be played on the board
void draw_piece_priority_array(int piece_idx_priority_array[NB_OF_PIECES], int piece_selected, int nb_of_playable_pieces, bool playable_side_per_piece_idx_mask[NB_OF_PIECES][MAX_NB_OF_SIDE_PER_PIECE])
{
    static Piece piece_priority_array[NB_OF_PIECES] = {0};
    static Piece piece_remaining_array[NB_OF_PIECES] = {0};

    // to position the legend display to the bottom of the columns
    static Vector2_int priority_legend_pos;
    static Vector2_int remaining_legend_pos;

    static Vector2_int priority_base_pos = (Vector2_int){-8, 0};  // leftmost column is the display of priority array
    static Vector2_int remaining_base_pos = (Vector2_int){-4, 0}; // remaining pieces of the priority array are displayed to the left of the board in a column

    static const int rotation_state = 0;
    static int side_idx = 0;

    // temp variables for iteration
    static int i;
    static Piece *piece;
    static int piece_idx;

    static bool is_first_call = true;
    static bool need_update = false;

    if (is_first_call)
    {
        is_first_call = false;

        priority_legend_pos = (Vector2_int){offset_px.i - small_tile_px_width * 9, offset_px.j + small_tile_px_width * 19 + 10};
        remaining_legend_pos = (Vector2_int){offset_px.i - small_tile_px_width * 5 + 10, offset_px.j + small_tile_px_width * 19 + 10};

        load_piece_array(piece_priority_array);
        load_piece_array(piece_remaining_array);
        need_update = true;
    }

    else
        need_update = (piece_selected == 0 || piece_selected == 1);

    // need to be reset at each call
    remaining_base_pos.j = 19;
    priority_base_pos.j = 19;

    // small piece display setup, (global constants swap)
    current_tile_px_width = small_tile_px_width;
    current_connection_line_px_thick = small_connection_line_px_thick;
    current_outline_px_thick = small_outline_px_thick;
    current_bend_circle_radius = small_bend_circle_radius;
    current_point_circle_radius = small_point_circle_radius;
    current_connections_tip_offset = small_connections_tip_offset;

    // fill columns from the bottom up
    if (need_update)
    {
        for (i = nb_of_playable_pieces - 1; i >= 0; i--)
        {
            piece_idx = piece_idx_priority_array[i];

            // To show the choosen point pieces with their point side
            // And avoiding showing point side of other pieces
            side_idx = 0;
            if (!playable_side_per_piece_idx_mask[piece_idx][side_idx])
                side_idx = 1;

            // Piece priority array update
            piece = piece_priority_array + piece_idx;
            priority_base_pos.j -= piece->piece_height;
            blit_piece_main_data(piece, side_idx, priority_base_pos, rotation_state);
            priority_base_pos.j--; // let a space of 1 small-tile between 2 pieces
            update_piece_all_drawing(piece, false, false);

            // Remaining pieces udpate
            if (i < piece_selected)
                continue;
            piece = (piece_remaining_array) + piece_idx;
            remaining_base_pos.j -= piece->piece_height;
            blit_piece_main_data(piece, side_idx, remaining_base_pos, rotation_state);
            remaining_base_pos.j--; // let a space of 1 small-tile between 2 pieces
            update_piece_all_drawing(piece, false, false);
        }
    }

    for (i = nb_of_playable_pieces - 1; i >= 0; i--)
    {
        piece_idx = piece_idx_priority_array[i];

        // Piece priority array display
        piece = piece_priority_array + piece_idx;
        draw_piece(piece, false, false);

        if (i < piece_selected)
            continue;
        piece = (piece_remaining_array) + piece_idx;
        draw_piece(piece, false, false);
    }

    // Restore normal drawing constants
    current_tile_px_width = tile_px_width;
    current_connection_line_px_thick = connection_line_px_thick;
    current_outline_px_thick = outline_px_thick;
    current_bend_circle_radius = bend_circle_radius;
    current_point_circle_radius = point_circle_radius;
    current_connections_tip_offset = connections_tip_offset;

    // Drawing legends
    DrawText("Piece order", priority_legend_pos.i, priority_legend_pos.j, 20, RAYWHITE);
    DrawText("Remaining", remaining_legend_pos.i, remaining_legend_pos.j, 20, RAYWHITE);
}

// -----------------------------------------------------------------------------------------------------------------------------------------
// -------------------------- GUI for screen_game.c and screen_solver.c --------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------

void draw_game_controls(void)
{
    static int line;
    static int offset_x = 1150;
    static int legend_offset_x = 220;
    static int offset_y = 150;
    static int font_size = 20;
    static int line_extra_spacing = 2;

    line = 0;

    DrawText("Controls :", offset_x, offset_y, font_size, RAYWHITE);
    line += 2;
    DrawText("\t- ZQSD (or WASD)", offset_x, offset_y + line * (font_size + line_extra_spacing), font_size, RAYWHITE);
    DrawText(": Move piece accross the board", offset_x + legend_offset_x, offset_y + line * (font_size + line_extra_spacing), font_size, RAYWHITE);
    line++;
    DrawText("\t- F", offset_x, offset_y + line * (font_size + line_extra_spacing), font_size, RAYWHITE);
    DrawText(": Change piece's side", offset_x + legend_offset_x, offset_y + line * (font_size + line_extra_spacing), font_size, RAYWHITE);
    line++;
    DrawText("\t- R", offset_x, offset_y + line * (font_size + line_extra_spacing), font_size, RAYWHITE);
    DrawText(": Rotate piece clockwise", offset_x + legend_offset_x, offset_y + line * (font_size + line_extra_spacing), font_size, RAYWHITE);
    line++;
    DrawText("\t- C", offset_x, offset_y + line * (font_size + line_extra_spacing), font_size, RAYWHITE);
    DrawText(": Change selected piece", offset_x + legend_offset_x, offset_y + line * (font_size + line_extra_spacing), font_size, RAYWHITE);
    line += 2;
    DrawText("\t- SPACE", offset_x, offset_y + line * (font_size + line_extra_spacing), font_size, RAYWHITE);
    DrawText(": Add piece to board", offset_x + legend_offset_x, offset_y + line * (font_size + line_extra_spacing), font_size, RAYWHITE);
    line++;
    DrawText("\t- E", offset_x, offset_y + line * (font_size + line_extra_spacing), font_size, RAYWHITE);
    DrawText(": Undo last piece adding", offset_x + legend_offset_x, offset_y + line * (font_size + line_extra_spacing), font_size, RAYWHITE);
    line += 2;
    DrawText("\t- ESCAPE", offset_x, offset_y + line * (font_size + line_extra_spacing), font_size, RAYWHITE);
    DrawText(": Go back to level selection", offset_x + legend_offset_x, offset_y + line * (font_size + line_extra_spacing), font_size, RAYWHITE);
}

int draw_game_mode_choice(void)
{
    static int active = 1;
    static int spacing = 32;
    static Rectangle bounds = (Rectangle){1200, 460, 199, 40};

    DrawText("Mode :", 1150, 460 - spacing, 20, RAYWHITE);

    active = GuiToggleGroup(bounds, "FREE;ASSISTED", active);

    return active;
}

void draw_separator(void)
{
    DrawText("---------------- Solver Parameters ----------------", 1150, 560, 20, RAYWHITE);
}

int draw_FPS_choice(void)
{
    static int active = 2;
    static int spacing = 32;
    static Rectangle bounds = (Rectangle){1200, 630, 55, 40};

    DrawText("FPS :", 1150, 630 - spacing, 20, RAYWHITE);

    active = GuiToggleGroup(bounds, "0;1;3;10;30;60;INF", active);

    if (active == 0)
        DrawText("Press SPACE to go to next frame", 1200, 630 + 40 + 5, 20, ORANGE);

    return active;
}

bool draw_launch_button(void)
{

    static Rectangle bounds = (Rectangle){1200, 730, 400, 40};
    return GuiButton(bounds, "Launch solver !");
}

// Function to draw the result hint after adding a piece to the board in assisted mode
//  make status + 10 if the error code come from "run_all_checks" instead of "add_piece_to_board"
void draw_board_validation(int status)
{

    static int x = 330, y = 700, font_size = 20;
    static Color col = RAYWHITE;

    switch (status)
    {
    case 0:

        DrawText("Board validation : Waiting for user to add a piece", x, y, font_size, col);
        break;

    case 1:
        DrawText("Board validation : Successfully added piece", x, y, font_size, col);
        break;

    case OUT_OF_BOUNDS:
        DrawText("Board validation : Error ! One or more tiles|connections are out of bounds", x, y, font_size, col);
        break;
    case SUPERPOSED_TILES:
        DrawText("Board validation : Error ! One or more tiles are superposed", x, y, font_size, col);
        break;
    case TILE_NOT_MATCHING_MISSING_CONNECTIONS:
        DrawText("Board validation : Error ! Connections are not right", x, y, font_size, col);
        break;
    case TILE_NOT_MATCHING_LEVEL_HINTS:
        DrawText("Board validation : Error ! One or more tiles don't match level hints", x, y, font_size, col);
        break;
    case TRIPLE_MISSING_CONNECTION_TILE:
        DrawText("Board validation : Error ! A position is expecting 3 connections (not allowed)", x, y, font_size, col);
        break;
    case INVALID_DOUBLE_MISSING_CONNECTION:
        DrawText("Board validation : Error ! A position is expecting 2 connections and can't", x, y, font_size, col);
        DrawText("be filled with remaining pieces", x, y + font_size + 1, font_size, col);
        break;
    case 10 + ISOLATED_EMPTY_TILE:
        DrawText("Board validation : Error ! One or more positions are isolated", x, y, font_size, col);
        break;
    case 10 + DEAD_END:
        DrawText("Board validation : Error ! There is a connection path dead end", x, y, font_size, col);
        break;
    case 10 + DOUBLE_MISSING_CONNECTION_NOT_FILLABLE:
        DrawText("Board validation : Error ! A position is expecting 2 connections and can't", x, y, font_size, col);
        DrawText("be filled with remaining pieces", x, y + font_size + 1, font_size, col);
        break;
    case 10 + LOOP_PATH:
        DrawText("Board validation : Error ! There is a connection path loop (not allowed)", x, y, font_size, col);
        break;

    // special cases to display undo operation logs
    case UNDO_SUCCESS:
        DrawText("Board undo       : Successfully removed piece", x, y, font_size, col);
        break;
    case UNDO_ERROR:
        DrawText("Board undo       : Error ! There is no piece to remove", x, y, font_size, col);
        DrawText("(Or these are part of level hints)", x, y + font_size + 1, font_size, col);
        break;

    // special case : board completed
    case BOARD_COMPLETED:
        DrawText("Board completed !", x, y, font_size, col);
        break;

    case ALL_PIECE_PLAYED:
        DrawText("All pieces have been played !", x, y, font_size, col);
        break;

    default:
        break;
    }
}

void draw_solver_result(bool successful_ending, double total_time, int valid_board_count)
{
    static int x = 330, y = 700, font_size = 20;
    static Color col = RAYWHITE;

    static char sub_string[20];

    if (successful_ending)
        sprintf(sub_string, "Complete !");
    else
        sprintf(sub_string, "No solution !");

    DrawText(TextFormat("%s | Time : %.4fs | Valid board count : %d", sub_string, (float)total_time, valid_board_count), x, y, font_size, col);
}