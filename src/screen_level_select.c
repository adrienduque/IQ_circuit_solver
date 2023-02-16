/**
 * @file screen_level_select.c
 * @see screens.h
 *
 * File containing Update and Draw functions for the level selection screen, see screens.h and raylib game templates
 */

#include <stdio.h> // sprintf

#include <raylib/raylib.h>
#include <raylib/raygui.h>

#include <local/display.h> // gui_icon_scale
#include <local/utils.h>   // assets_folder_relative_path

#include <raylib/screens.h>

#define START_LEVEL 49
#define NB_OF_LEVELS 72

#define NB_OF_ROWS 3
#define NB_OF_COLS 4

#define NB_OF_LEVELS_PER_PAGE 12 // NB_OF_ROWS * NB_OF_COLS
#define NB_OF_PAGES 6            // NB_OF_LEVELS / NB_OF_LEVELS_PER_PAGE (has to be a whole number !)

static Texture2D level_texture_array[NB_OF_LEVELS];
static Rectangle level_hitbox;
static int texture_px_width, texture_px_height, grid_spacing_px_x, grid_spacing_px_y, font_size, constant_offset_y;

static int current_page, current_page_first_index, selected_index, finishScreen;

static Rectangle logo_hitbox;
static Texture2D logo_texture;
static bool is_mouse_over_logo;

static int button_spacing_from_center;
static Rectangle right_button_hitbox, left_button_hitbox;

int level_num_selected; // global variable shared between modules

void InitLevelSelectScreen(void)
{
    static Image image_logo;

    image_logo = LoadImage(TextFormat("%s/IQ_circuit_official_logo.png", assets_folder_relative_path));
    ImageResize(&image_logo, (int)(image_logo.width / 4), (int)(image_logo.height / 4));
    logo_texture = LoadTextureFromImage(image_logo);
    UnloadImage(image_logo);
    logo_hitbox = (Rectangle){GetScreenWidth() - 30 - logo_texture.width, 30, logo_texture.width, logo_texture.height};
    is_mouse_over_logo = false;

    for (int i = 0; i < NB_OF_LEVELS; i++)
        level_texture_array[i] = LoadTexture(TextFormat("%s/level_frames/%d.png", assets_folder_relative_path, i + START_LEVEL));

    texture_px_width = level_texture_array[0].width;
    texture_px_height = level_texture_array[0].height;

    grid_spacing_px_x = (int)((GetScreenWidth() - NB_OF_COLS * texture_px_width) / (NB_OF_COLS + 1));
    grid_spacing_px_y = (int)((GetScreenHeight() - NB_OF_ROWS * texture_px_height) / (NB_OF_ROWS + 1));

    constant_offset_y = (int)(grid_spacing_px_y / 2);
    font_size = (int)(grid_spacing_px_y / 3);

    level_hitbox = (Rectangle){0, 0, texture_px_width, texture_px_height};

    button_spacing_from_center = 230;

    left_button_hitbox = (Rectangle){(int)(GetScreenWidth() / 2 - button_spacing_from_center) - DEFAULT_ICON_PIXEL_SIZE * gui_icon_scale, constant_offset_y - 10, DEFAULT_ICON_PIXEL_SIZE * gui_icon_scale, DEFAULT_ICON_PIXEL_SIZE * gui_icon_scale};
    right_button_hitbox = (Rectangle){(int)(GetScreenWidth() / 2 + button_spacing_from_center), constant_offset_y - 10, DEFAULT_ICON_PIXEL_SIZE * gui_icon_scale, DEFAULT_ICON_PIXEL_SIZE * gui_icon_scale};

    // ----------------

    current_page = 0;
    current_page_first_index = current_page * NB_OF_LEVELS_PER_PAGE;
    selected_index = -1;

    finishScreen = 0;
}

void UpdateLevelSelectScreen(void)
{
    static int index;

    finishScreen = 0;

    // Page update
    if (GuiButton(left_button_hitbox, GuiIconText(ICON_ARROW_LEFT_FILL, NULL)) || IsKeyPressed(KEY_LEFT))
        current_page -= (current_page == 0) ? 0 : 1;

    if (GuiButton(right_button_hitbox, GuiIconText(ICON_ARROW_RIGHT_FILL, NULL)) || IsKeyPressed(KEY_RIGHT))
        current_page += (current_page == NB_OF_PAGES - 1) ? 0 : 1;

    // Level selection on displayed level thumbnails
    selected_index = -1;
    current_page_first_index = current_page * NB_OF_LEVELS_PER_PAGE;

    is_mouse_over_logo = false;
    if (CheckCollisionPointRec(GetMousePosition(), logo_hitbox))
    {
        is_mouse_over_logo = true;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            OpenURL("https://www.smartgames.eu/uk/one-player-games/iq-circuit");
        return;
    }

    for (int j = 0; j < NB_OF_ROWS; j++)
    {
        for (int i = 0; i < NB_OF_COLS; i++)
        {

            index = current_page_first_index + i + NB_OF_COLS * j;

            level_hitbox.x = grid_spacing_px_x + (grid_spacing_px_x + texture_px_width) * i;
            level_hitbox.y = grid_spacing_px_y + (grid_spacing_px_y + texture_px_height) * j + constant_offset_y;

            if (CheckCollisionPointRec(GetMousePosition(), level_hitbox))
            {
                selected_index = index;
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    level_num_selected = index + START_LEVEL;
                    finishScreen = 1;
                }
                return;
            }
        }
    }
}
void DrawLevelSelectScreen(void)
{
    static int i, j, index, real_index;
    static Color col;
    static char *presentation_string = "Choose a level to solve !";

    ClearBackground(BLACK);

    DrawText(presentation_string, (int)(GetScreenWidth() / 2 - MeasureText(presentation_string, font_size) / 2), constant_offset_y, font_size, RAYWHITE);

    for (j = 0; j < NB_OF_ROWS; j++)
    {
        for (i = 0; i < NB_OF_COLS; i++)
        {

            index = current_page_first_index + i + NB_OF_COLS * j;
            real_index = index + START_LEVEL;

            col = (index == selected_index) ? ORANGE : RAYWHITE;

            level_hitbox.x = grid_spacing_px_x + (grid_spacing_px_x + texture_px_width) * i;
            level_hitbox.y = grid_spacing_px_y + (grid_spacing_px_y + texture_px_height) * j + constant_offset_y;

            DrawTexture(level_texture_array[index], level_hitbox.x, level_hitbox.y, col);
            DrawText(TextFormat("%d", real_index), level_hitbox.x, level_hitbox.y - font_size - 7, font_size, ORANGE);
            DrawRectangleRoundedLines(level_hitbox, 0.1, 30, 6, col);
        }
    }

    DrawTexture(logo_texture, logo_hitbox.x, logo_hitbox.y, is_mouse_over_logo ? ORANGE : WHITE);
    DrawRectangleRoundedLines(logo_hitbox, 0.1, 15, 2, is_mouse_over_logo ? ORANGE : WHITE);
    DrawText("from Raf Peeters", logo_hitbox.x - 2, logo_hitbox.y + logo_hitbox.height + 5, 10, is_mouse_over_logo ? GOLD : RAYWHITE);
}

void UnloadLevelSelectScreen(void)
{
    for (int i = 0; i < NB_OF_LEVELS; i++)
        UnloadTexture(level_texture_array[i]);

    UnloadTexture(logo_texture);
}

int FinishLevelSelectScreen(void)
{
    return finishScreen;
}