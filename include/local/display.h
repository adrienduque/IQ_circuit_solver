/**
 * @file display.h
 * @see display.c
 */

#include <local/utils.h>
#include <raylib/raylib.h>
#include <local/piece.h>
#include <stdbool.h>

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

void setup_display();
void DrawLineStripEx(Vector2 *points, int pointCount, float thick, Color color);
void draw_tile_color(Tile tile, Color connection_color);
void draw_tile(Tile tile);
void draw_missing_connection_tile(Tile tile);
void draw_border_tile(int flat_pos);
void draw_outline_edge_points(RelativePos *outline_edge_points, int nb_of_edge_points);
void draw_grid();

#endif