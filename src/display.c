/**
 * @file display.c
 *
 * File containing all graphic display functions used for the main algorithm visualization and debugging
 * Based on the raylib API
 *
 * @warning pixel display is basically mapped to 2D indexing of tiles by : (px,py) = (i,j) * tile_px_width
 * @see utils.h and utils.c
 * To create a margin between the edge of the display window and the grid drawing, a number of padding tiles is used.
 * The mapping of a tile (i,j) to pixel (px,py), becomes : (px,py) = (i+nb_padding_tile,j+nb_padding_tile) * tile_px_width
 *
 * The same idea of caching is used for drawing data
 * At each different drawing section there is :
 * 1) Function to compute cache drawing data, used only when they need to be updated (e.g : piece moving on the board)
 * 2) Function to effectively draw the cached data (which is repeated in classic drawing loops)
 *
 */

#include <local/display.h>

// -------------------------- Static drawing constants ------------------------------------

// Main global parameters
static const int tile_px_width = 101;
static const int nb_padding_tile = 1;

static Color connection_line_color = {212, 175, 55, 255};
static Color outline_color = {200, 255, 0, 255};

// Driven parameters
static const int grid_line_px_thick = tile_px_width / 10;
static const int connection_line_px_thick = grid_line_px_thick;
static const int outline_px_thick = tile_px_width / 25;

static const int total_px_width = tile_px_width * (BOARD_WIDTH + 2 * nb_padding_tile);
static const int total_px_height = tile_px_width * (BOARD_HEIGHT + 2 * nb_padding_tile);

// ---------------------------------------------------------------------------------------------------------------
// --------------------------------- Manually extending raylib ---------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------

// Function to initialize a raylib window
void setup_display()
{

    static bool is_display_setup = false;
    if (is_display_setup)
        return;
    is_display_setup = true;
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(total_px_width, total_px_height, "Raylib Board Visualization");
}

// Function to add on top of raylib library : DrawLineStrip function but with a thickness option
void DrawLineStripEx(Vector2 *points, int pointCount, float thick, Color color)
{
    for (int i = 0; i < pointCount - 1; i++)
        DrawLineEx(points[i], points[i + 1], thick, color);
}

// ---------------------------------------------------------------------------------------------------------------
// ---------------------------------- Main elementary drawing sub functions --------------------------------------
// ---------------------------------------------------------------------------------------------------------------

// Function to draw the background grid of the game board
/**
 * @warning depreciated function still used in test_display.c, new function -> load_draw_grid_data + draw_board_grid
 */
void draw_grid()
{
    float pt_x, pt_y, pt1_y, pt2_y, pt1_x, pt2_x;
    Vector2 start_point, end_point;
    for (int idx = nb_padding_tile; idx <= (BOARD_WIDTH + nb_padding_tile); idx++)
    {
        pt_x = idx * tile_px_width;
        pt1_y = nb_padding_tile * tile_px_width;
        pt2_y = (nb_padding_tile + BOARD_HEIGHT) * tile_px_width;
        start_point.x = pt_x;
        start_point.y = pt1_y;
        end_point.x = pt_x;
        end_point.y = pt2_y;

        DrawLineEx(start_point, end_point, grid_line_px_thick, GRAY);
    }
    for (int idx = nb_padding_tile; idx <= (BOARD_HEIGHT + nb_padding_tile); idx++)
    {
        pt_y = idx * tile_px_width;
        pt1_x = nb_padding_tile * tile_px_width;
        pt2_x = (nb_padding_tile + BOARD_WIDTH) * tile_px_width;
        start_point.x = pt1_x;
        start_point.y = pt_y;
        end_point.x = pt2_x;
        end_point.y = pt_y;

        DrawLineEx(start_point, end_point, grid_line_px_thick, GRAY);
    }
}

void load_draw_grid_data(Board *board)
{
    float pt_x, pt_y, pt1_y, pt2_y, pt1_x, pt2_x;
    int current_point_couple_idx = 0;
    for (int idx = nb_padding_tile; idx <= (BOARD_WIDTH + nb_padding_tile); idx++)
    {
        pt_x = idx * tile_px_width;
        pt1_y = nb_padding_tile * tile_px_width;
        pt2_y = (nb_padding_tile + BOARD_HEIGHT) * tile_px_width;
        board->grid_lines_pt_array[current_point_couple_idx][0].x = pt_x;
        board->grid_lines_pt_array[current_point_couple_idx][0].y = pt1_y;
        board->grid_lines_pt_array[current_point_couple_idx][1].x = pt_x;
        board->grid_lines_pt_array[current_point_couple_idx][1].y = pt2_y;

        current_point_couple_idx++;
    }
    for (int idx = nb_padding_tile; idx <= (BOARD_HEIGHT + nb_padding_tile); idx++)
    {
        pt_y = idx * tile_px_width;
        pt1_x = nb_padding_tile * tile_px_width;
        pt2_x = (nb_padding_tile + BOARD_WIDTH) * tile_px_width;

        board->grid_lines_pt_array[current_point_couple_idx][0].x = pt1_x;
        board->grid_lines_pt_array[current_point_couple_idx][0].y = pt_y;
        board->grid_lines_pt_array[current_point_couple_idx][1].x = pt2_x;
        board->grid_lines_pt_array[current_point_couple_idx][1].y = pt_y;

        current_point_couple_idx++;
    }
}

void draw_board_grid(Board *board)
{
    for (int i = 0; i < NB_OF_GRID_LINES; i++)
        DrawLineEx(board->grid_lines_pt_array[i][0], board->grid_lines_pt_array[i][1], grid_line_px_thick, GRAY);
}

// ------------- Drawing normal and missing_connection tiles

// values to add from center x,y, to get the other point of the line to draw the connection in the right direction
// see load_draw_tile_data when it treats connection lines
static Vector2_int connections_display_offset[] = {
    [RIGHT] = {tile_px_width / 2, 0},
    [DOWN] = {0, tile_px_width / 2},
    [LEFT] = {-tile_px_width / 2, 0},
    [UP] = {0, -tile_px_width / 2},
};

// Function to compute one time dynamic drawing data per tile
// That drawing tile functions use repeatedly
void load_draw_tile_data(Tile *tile)
{
    static Direction connection_direction;

    tile->effective_absolute_pos.i = tile->absolute_pos.i + nb_padding_tile;
    tile->effective_absolute_pos.j = tile->absolute_pos.j + nb_padding_tile;

    tile->top_left_corner_pt.i = tile->effective_absolute_pos.i * tile_px_width;
    tile->top_left_corner_pt.j = tile->effective_absolute_pos.j * tile_px_width;

    tile->center_pt.x = tile->top_left_corner_pt.i + tile_px_width / 2;
    tile->center_pt.y = tile->top_left_corner_pt.j + tile_px_width / 2;

    for (int idx = 0; idx < tile->nb_of_connections; idx++)
    {
        connection_direction = tile->connection_direction_array[idx];
        tile->connection_pt_array[idx].x = tile->center_pt.x + connections_display_offset[connection_direction].i;
        tile->connection_pt_array[idx].y = tile->center_pt.y + connections_display_offset[connection_direction].j;
    }
}

// Function to draw a blitted tile
static void draw_tile_color(Tile *tile, Color connection_color)
{
    for (int i = 0; i < tile->nb_of_connections; i++)
    {
        DrawLineEx(tile->center_pt, tile->connection_pt_array[i], connection_line_px_thick, connection_color);
    }

    if (tile->tile_type == bend)
    {
        DrawCircle((int)tile->center_pt.x, (int)tile->center_pt.y, (float)(connection_line_px_thick / 2 - 1), connection_color);
    }
    else if (tile->tile_type == point)
    {
        DrawCircle((int)tile->center_pt.x, (int)tile->center_pt.y, (float)(tile_px_width / 6), connection_color);
    }

    DrawRectangleLines(tile->top_left_corner_pt.i, tile->top_left_corner_pt.j, tile_px_width, tile_px_width, WHITE);
}

// shortcut to draw normal tiles with connection color : gold
// see draw_tile_color
void draw_tile(Tile *tile)
{
    draw_tile_color(tile, connection_line_color);
}

// shortcut to draw missing connection tiles with connection color : red
// see draw_tile_color
// these are separate functions, because I might only use it to debug the data and not use it in the main visualization
void draw_missing_connection_tile(Tile *tile)
{
    draw_tile_color(tile, RED);
}

// ----------------- Drawing border tiles (only used in debugging see test_display.c)

void load_draw_border_tile_data(Piece *piece)
{

    for (int idx = 0; idx < piece->nb_of_border_tiles; idx++)
    {
        if (!is_pos_valid(&(piece->border_tile_absolute_pos_array[idx])))
        {
            set_invalid_pos(&(piece->border_tile_effective_absolute_top_left_corner_pt_array[idx]));
            continue;
        }
        piece->border_tile_effective_absolute_top_left_corner_pt_array[idx].i = (piece->border_tile_absolute_pos_array[idx].i + nb_padding_tile) * tile_px_width;
        piece->border_tile_effective_absolute_top_left_corner_pt_array[idx].j = (piece->border_tile_absolute_pos_array[idx].j + nb_padding_tile) * tile_px_width;
    }
}
void draw_border_tiles(Piece *piece)
{
    static Rectangle rec;
    for (int idx = 0; idx < piece->nb_of_border_tiles; idx++)
    {
        if (!is_pos_valid(&(piece->border_tile_effective_absolute_top_left_corner_pt_array[idx])))
            continue;
        rec.x = (float)(piece->border_tile_effective_absolute_top_left_corner_pt_array[idx].i);
        rec.y = (float)(piece->border_tile_effective_absolute_top_left_corner_pt_array[idx].j);
        rec.width = (float)tile_px_width;
        rec.height = (float)tile_px_width;

        DrawRectangleLinesEx(rec, (float)outline_px_thick, SKYBLUE);
    }
}

// ----------------- Drawing outline edge of pieces

void load_draw_outline_tile_data(Piece *piece)
{
    for (int idx = 0; idx < piece->nb_of_outline_tiles; idx++)
    {
        piece->outline_tile_effective_absolute_top_left_corner_pt_array[idx].x = (piece->outline_tile_absolute_pos_array[idx].i + nb_padding_tile) * tile_px_width;
        piece->outline_tile_effective_absolute_top_left_corner_pt_array[idx].y = (piece->outline_tile_absolute_pos_array[idx].j + nb_padding_tile) * tile_px_width;
    }
}
void draw_outline_edge_points(Piece *piece)
{
    DrawLineStripEx(piece->outline_tile_effective_absolute_top_left_corner_pt_array, piece->nb_of_outline_tiles, outline_px_thick, outline_color);
}

// ---------------------------------------------------------------------------------------------------------------
// ---------------------------------- Convenience functions --------------------------------------
// ---------------------------------------------------------------------------------------------------------------

void update_all_piece_draw_data(Piece *piece, bool show_missing_connection_tiles, bool show_border_tiles)
{
    static Tile *current_tile;
    for (int i = 0; i < piece->side_array[piece->current_side_idx].nb_of_tiles; i++)
    {
        current_tile = (piece->side_array[piece->current_side_idx].tile_array) + i;
        load_draw_tile_data(current_tile);
    }
    if (show_missing_connection_tiles)
    {
        for (int i = 0; i < piece->side_array[piece->current_side_idx].nb_of_missing_connection_tiles; i++)
        {
            current_tile = (piece->side_array[piece->current_side_idx].missing_connection_tile_array) + i;
            load_draw_tile_data(current_tile);
        }
    }
    if (show_border_tiles)
        load_draw_border_tile_data(piece);
    load_draw_outline_tile_data(piece);
}

void draw_all_piece_data(Piece *piece, bool show_missing_connection_tiles, bool show_border_tiles)
{

    static Tile *current_tile;
    for (int i = 0; i < piece->side_array[piece->current_side_idx].nb_of_tiles; i++)
    {
        current_tile = (piece->side_array[piece->current_side_idx].tile_array) + i;
        draw_tile(current_tile);
    }
    if (show_missing_connection_tiles)
    {
        for (int i = 0; i < piece->side_array[piece->current_side_idx].nb_of_missing_connection_tiles; i++)
        {
            current_tile = (piece->side_array[piece->current_side_idx].missing_connection_tile_array) + i;
            draw_missing_connection_tile(current_tile);
        }
    }

    if (show_border_tiles)
        draw_border_tiles(piece);

    draw_outline_edge_points(piece);
}
