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

// --------------------------------- Manually extending raylib ---------------------------------------------------

// Function to add on top of raylib library : DrawLineStrip function but with a thickness option
void DrawLineStripEx(Vector2 *points, int pointCount, float thick, Color color)
{
    for (int i = 0; i < pointCount - 1; i++)
        DrawLineEx(points[i], points[i + 1], thick, color);
}

// ---------------------------------- Main elementary drawing sub functions --------------------------------------

// values to add from center x,y, to get the other point of the line to draw the connection in the right direction
// see draw_tile_color when it draws connection lines
static RelativePos connections_display_offset[] = {
    [RIGHT] = {tile_px_width / 2, 0},
    [DOWN] = {0, tile_px_width / 2},
    [LEFT] = {-tile_px_width / 2, 0},
    [UP] = {0, -tile_px_width / 2},
};

// Function to draw a blitted tile
void draw_tile_color(Tile tile, Color connection_color)
{
    RelativePos pos = flat_pos_to_relative_pos(tile.flat_position);
    pos.i += nb_padding_tile;
    pos.j += nb_padding_tile;

    Vector2 center;
    center.x = pos.i * tile_px_width + tile_px_width / 2;
    center.y = pos.j * tile_px_width + tile_px_width / 2;

    Vector2 connection_point;

    for (int i = 0; i < tile.nb_of_connections; i++)
    {
        Direction connection_direction = tile.connection_direction_array[i];
        connection_point.x = center.x + connections_display_offset[connection_direction].i;
        connection_point.y = center.y + connections_display_offset[connection_direction].j;
        DrawLineEx(center, connection_point, connection_line_px_thick, connection_color);
    }

    if (tile.tile_type == bend)
    {
        DrawCircle((int)center.x, (int)center.y, (float)(connection_line_px_thick / 2 - 1), connection_color);
    }
    else if (tile.tile_type == point)
    {
        DrawCircle((int)center.x, (int)center.y, (float)(tile_px_width / 6), connection_color);
    }

    DrawRectangleLines(pos.i * tile_px_width, pos.j * tile_px_width, tile_px_width, tile_px_width, WHITE);
}

// shortcut to draw normal tiles with connection color : gold
// see draw_tile_color
void draw_tile(Tile tile)
{
    draw_tile_color(tile, connection_line_color);
}

// shortcut to draw missing connection tiles with connection color : red
// see draw_tile_color
// these are separate functions, because I might only use it to debug the data and not use it in the main visualization
void draw_missing_connection_tile(Tile tile)
{
    draw_tile_color(tile, RED);
}

// Function to debug blitted border tiles of pieces by drawing them
void draw_border_tile(int flat_pos)
{
    if (!is_flat_pos_valid(flat_pos))
        return;
    RelativePos pos = flat_pos_to_relative_pos(flat_pos);
    pos.i += nb_padding_tile;
    pos.j += nb_padding_tile;
    DrawRectangleLines(pos.i * tile_px_width, pos.j * tile_px_width, tile_px_width, tile_px_width, SKYBLUE);
}

// Function to draw blitted outline edge points of a piece
void draw_outline_edge_points(RelativePos *outline_edge_points, int nb_of_edge_points)
{
    // we assume that outline_edge_points has already been blitted
    Vector2 points[nb_of_edge_points];
    for (int i = 0; i < nb_of_edge_points; i++)
    {
        points[i].x = (outline_edge_points[i].i + nb_padding_tile) * tile_px_width;
        points[i].y = (outline_edge_points[i].j + nb_padding_tile) * tile_px_width;
    }

    DrawLineStripEx(points, nb_of_edge_points, outline_px_thick, outline_color);
}

// Function to draw the background grid of the game board
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
