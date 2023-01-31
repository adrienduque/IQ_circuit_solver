/**
 * @file astar.c
 * File that contains a custom implementation of the a-star pathfinding algorithm
 *
 * (has a starting position on the board, a target ending position, and can only explore the empty tiles on the board (all the tiles except the ones filled with normal tiles))
 * (also, the board actually have multiple valid targets, the pathfinding algorithm will try to go toward the ending target, but if the algorithm ends up on another one, it returns)
 * (returns the final tile or UNDEFINED_TILE (alias for NULL); not the actual path it took to get here)
 *
 * It is needed in check_board.c > check_no_dead_ends
 */

#include <stdlib.h> //malloc and free, NULL
#include <limits.h> // INT_MAX

#include <local/utils.h>      // Vector2_int, Direction, manhattan_dist, other helper functions, defines
#include <local/board.h>      // Board, extract_normal_tile_at_pos, UNDEFINED_TILE
#include <local/piece_data.h> // Tile

#include <local/astar.h>

typedef struct OpenSetElement
{
    int f, h;
    Vector2_int pos;

    struct OpenSetElement *next;

} OpenSetElement;

static void free_open_set(OpenSetElement *open_set_element)
{
    // recursive free basically
    // to free the pointers, last one first

    if (open_set_element == NULL)
        return;

    free_open_set(open_set_element->next);
    free(open_set_element);
}

// Working version of the pathfinding with dynamic memory allocation
Tile *find_a_path_(Board *board, Vector2_int *start_pos, Vector2_int *target_pos, SimpleTileType board_representation_matrix[BOARD_WIDTH][BOARD_HEIGHT])
{
    // A-star implementation :
    // we need a priority queue for the open_set, I'll not use a heapqueue though, as the open_set is of length n = BOARD_WIDTH*BOARD_HEIGHT maximum, and program heapify-up and down operations are a pain
    // a simple queue with priority enqueue will do the job
    // the g-scores are stored in a matrix of int
    // h is simply manhattan distance

    static int g_score_matrix[BOARD_WIDTH][BOARD_HEIGHT];
    static Tile *return_tile;
    static OpenSetElement *first_open_set_element, *current_open_set_element, *neighbour_element, *temp_open_set_element;
    static Direction direction;
    static Vector2_int neighbour_pos;
    static int temp_g_score;
    static int i, j;

    // g score matrix initialization
    for (i = 0; i < BOARD_WIDTH; i++)
    {
        for (j = 0; j < BOARD_HEIGHT; j++)
            g_score_matrix[i][j] = INT_MAX;
    }

    // initialization with start_pos
    g_score_matrix[start_pos->i][start_pos->j] = 0;

    first_open_set_element = malloc(sizeof(*first_open_set_element));

    first_open_set_element->f = manhattan_dist(start_pos, target_pos);
    first_open_set_element->pos.i = start_pos->i;
    first_open_set_element->pos.j = start_pos->j;
    first_open_set_element->next = NULL;

    while (first_open_set_element != NULL)
    {

        // pick the best f-score
        current_open_set_element = first_open_set_element;

        // successful ending condition
        if (board_representation_matrix[current_open_set_element->pos.i][current_open_set_element->pos.j] == target)
        {
            // we found a path, return the ending tile
            // store the ending tile before the free erase data
            return_tile = board->tile_matrix[current_open_set_element->pos.i][current_open_set_element->pos.j];
            free_open_set(first_open_set_element);
            return return_tile;
        }

        // remove element from open set
        first_open_set_element = first_open_set_element->next;

        // explore neighbours
        for (direction = RIGHT; direction < NB_OF_DIRECTIONS; direction++)
        {
            neighbour_pos = current_open_set_element->pos; // copy of values
            increment_pos_in_direction(&neighbour_pos, direction);

            // 1) we can explore every tile except walls

            // walls are defined as out of bound tiles, or "already filled with a normal tile" tiles
            if (!is_pos_inside_board(&neighbour_pos))
                continue;

            // successful ending condition
            if (board_representation_matrix[neighbour_pos.i][neighbour_pos.j] == target)
            {
                // we found a path, return the ending tile
                return_tile = board->tile_matrix[neighbour_pos.i][neighbour_pos.j];
                if (return_tile == UNDEFINED_TILE)
                    // it is actually a level tile
                    return_tile = board->obligatory_tile_matrix[neighbour_pos.i][neighbour_pos.j];
                free_open_set(first_open_set_element);
                free(current_open_set_element);
                return return_tile;
            }

            // early check to not backtrack
            temp_g_score = g_score_matrix[current_open_set_element->pos.i][current_open_set_element->pos.j] + 1;
            if (temp_g_score >= g_score_matrix[neighbour_pos.i][neighbour_pos.j])
                continue;

            // actual wall checking
            if ((board_representation_matrix[neighbour_pos.i][neighbour_pos.j] != no_info))
            {
                if (board_representation_matrix[neighbour_pos.i][neighbour_pos.j] == wall)
                    continue;
            }
            else
            {
                // we have to determine if the tile is a wall or not (already occupied by a normal tile or not)
                if (extract_normal_tile_at_pos(board, &neighbour_pos) == UNDEFINED_TILE)
                    // build cache for later
                    board_representation_matrix[neighbour_pos.i][neighbour_pos.j] = clear;

                else
                {
                    // build cache for later
                    board_representation_matrix[neighbour_pos.i][neighbour_pos.j] = wall;
                    continue;
                }
            }

            // 2) It is a valid neighbour to explore, add it to the open set while making sure it's sorted

            // sorted by ascending f-score
            // then also sorted by ascending h-score (for 2 equal f-score, prioritize the smallest h-score element)

            g_score_matrix[neighbour_pos.i][neighbour_pos.j] = temp_g_score;

            neighbour_element = malloc(sizeof(*neighbour_element));

            neighbour_element->h = manhattan_dist(&neighbour_pos, target_pos);
            neighbour_element->f = temp_g_score + neighbour_element->h;
            neighbour_element->pos.i = neighbour_pos.i;
            neighbour_element->pos.j = neighbour_pos.j;
            neighbour_element->next = NULL;

            // insert it in first, if open set is empty
            if (first_open_set_element == NULL)
            {
                first_open_set_element = neighbour_element;
                continue;
            }

            // insert it in first, if f-score is the minimum overall f-score
            // or if it has the same minimum overall f-score, but its h-score is smaller or equal
            if ((neighbour_element->f < first_open_set_element->f) || (neighbour_element->f == first_open_set_element->f && neighbour_element->h <= first_open_set_element->h))
            {
                neighbour_element->next = first_open_set_element;
                first_open_set_element = neighbour_element;
                continue;
            }

            // otherwise insert it in the middle of the queue according to its scores

            // we want the pointer preceding the future emplacement
            temp_open_set_element = first_open_set_element;

            // f-score sorting
            while (temp_open_set_element->next != NULL)
            {
                if (neighbour_element->f <= temp_open_set_element->next->f)
                    break;

                temp_open_set_element = temp_open_set_element->next;
            }

            // h-score sorting
            while (temp_open_set_element->next != NULL)
            {
                if (neighbour_element->f < temp_open_set_element->next->f)
                    break; // to account if there are multiple elements with the same f-score -> break as soon as the next one is greater than neighbour f-score (end of the list of the same f-score)

                if (neighbour_element->h <= temp_open_set_element->next->h)
                    break;

                temp_open_set_element = temp_open_set_element->next;
            }

            neighbour_element->next = temp_open_set_element->next;
            temp_open_set_element->next = neighbour_element;
        }

        free(current_open_set_element);
    }

    // Case where all possible tiles were explored but no path has been found

    return UNDEFINED_TILE;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------

// I'm trying a static memory allocation version
// which means, that I have to predict the maximum number of tile explored by the algorithm

#define MAX_NB_OF_TILE_EXPLORED BOARD_HEIGHT *BOARD_WIDTH * 10 // assuming the anti-backtrack feature of this algorithm is working, we can only explore each tile 4 times ? + margin to make sure
// (by doing experiments with the dynamic memory version of this algorithm, I actually found out that it never exceeded BOARD_HEIGHT*BOARD_WIDTH, but BOARD_HEIGHT*BOARD_WIDTH*10 is still a small number, so I'm not taking risks)

Tile *find_a_path(Board *board, Vector2_int *start_pos, Vector2_int *target_pos, SimpleTileType board_representation_matrix[BOARD_WIDTH][BOARD_HEIGHT])
{
    // A-star implementation :
    // we need a priority queue for the open_set, I'll not use a heapqueue though, as the open_set is of length n = BOARD_WIDTH*BOARD_HEIGHT maximum, and program heapify-up and down operations are a pain
    // a simple queue with priority enqueue will do the job
    // the g-scores are stored in a matrix of int
    // h is simply manhattan distance

    static int g_score_matrix[BOARD_WIDTH][BOARD_HEIGHT];
    static Tile *return_tile;
    static OpenSetElement *first_open_set_element, *current_open_set_element, *neighbour_element, *temp_open_set_element;
    static Direction direction;
    static Vector2_int neighbour_pos;
    static int temp_g_score;
    static int i, j;

    // static memory emplacements
    static OpenSetElement open_set_element_placeholders[BOARD_HEIGHT * BOARD_WIDTH * 10];
    static int nb_of_placeholders;

    // replacing all malloc calls by &(open_set_element_placeholders[nb_of_placeholders]); nb_of_placeholders++;
    // and getting rid of the free calls

    nb_of_placeholders = 0;

    // g score matrix initialization
    for (i = 0; i < BOARD_WIDTH; i++)
    {
        for (j = 0; j < BOARD_HEIGHT; j++)
            g_score_matrix[i][j] = INT_MAX;
    }

    // initialization with start_pos
    g_score_matrix[start_pos->i][start_pos->j] = 0;

    first_open_set_element = &(open_set_element_placeholders[nb_of_placeholders]);
    nb_of_placeholders++;

    first_open_set_element->f = manhattan_dist(start_pos, target_pos);
    first_open_set_element->pos.i = start_pos->i;
    first_open_set_element->pos.j = start_pos->j;
    first_open_set_element->next = NULL;

    while (first_open_set_element != NULL)
    {
        // pick the best f-score
        current_open_set_element = first_open_set_element;

        // successful ending condition
        if (board_representation_matrix[current_open_set_element->pos.i][current_open_set_element->pos.j] == target)
            // we found a path, return the ending tile
            return board->tile_matrix[current_open_set_element->pos.i][current_open_set_element->pos.j];

        // remove element from open set
        first_open_set_element = first_open_set_element->next;

        // explore neighbours
        for (direction = RIGHT; direction < NB_OF_DIRECTIONS; direction++)
        {
            neighbour_pos = current_open_set_element->pos; // copy of values
            increment_pos_in_direction(&neighbour_pos, direction);

            // 1) we can explore every tile except walls

            // walls are defined as out of bound tiles, or "already filled with a normal tile" tiles
            if (!is_pos_inside_board(&neighbour_pos))
                continue;

            // successful ending condition
            if (board_representation_matrix[neighbour_pos.i][neighbour_pos.j] == target)
            {
                // we found a path, return the ending tile
                return_tile = board->tile_matrix[neighbour_pos.i][neighbour_pos.j];
                if (return_tile == UNDEFINED_TILE)
                    // it is actually a level tile
                    return_tile = board->obligatory_tile_matrix[neighbour_pos.i][neighbour_pos.j];
                return return_tile;
            }

            // early check to not backtrack
            temp_g_score = g_score_matrix[current_open_set_element->pos.i][current_open_set_element->pos.j] + 1;
            if (temp_g_score >= g_score_matrix[neighbour_pos.i][neighbour_pos.j])
                continue;

            // actual wall checking
            if ((board_representation_matrix[neighbour_pos.i][neighbour_pos.j] != no_info))
            {
                if (board_representation_matrix[neighbour_pos.i][neighbour_pos.j] == wall)
                    continue;
            }
            else
            {
                // we have to determine if the tile is a wall or not (already occupied by a normal tile or not)
                if (extract_normal_tile_at_pos(board, &neighbour_pos) == UNDEFINED_TILE)
                    // build cache for later
                    board_representation_matrix[neighbour_pos.i][neighbour_pos.j] = clear;

                else
                {
                    // build cache for later
                    board_representation_matrix[neighbour_pos.i][neighbour_pos.j] = wall;
                    continue;
                }
            }

            // 2) It is a valid neighbour to explore, add it to the open set while making sure it's sorted

            // sorted by ascending f-score
            // then also sorted by ascending h-score (for 2 equal f-score, prioritize the smallest h-score element)

            g_score_matrix[neighbour_pos.i][neighbour_pos.j] = temp_g_score;

            neighbour_element = &(open_set_element_placeholders[nb_of_placeholders]);
            nb_of_placeholders++;

            neighbour_element->h = manhattan_dist(&neighbour_pos, target_pos);
            neighbour_element->f = temp_g_score + neighbour_element->h;
            neighbour_element->pos.i = neighbour_pos.i;
            neighbour_element->pos.j = neighbour_pos.j;
            neighbour_element->next = NULL;

            // insert it in first, if open set is empty
            if (first_open_set_element == NULL)
            {
                first_open_set_element = neighbour_element;
                continue;
            }

            // insert it in first, if f-score is the minimum overall f-score
            // or if it has the same minimum overall f-score, but its h-score is smaller or equal
            if ((neighbour_element->f < first_open_set_element->f) || (neighbour_element->f == first_open_set_element->f && neighbour_element->h <= first_open_set_element->h))
            {
                neighbour_element->next = first_open_set_element;
                first_open_set_element = neighbour_element;
                continue;
            }

            // otherwise insert it in the middle of the queue according to its scores

            // we want the pointer preceding the future emplacement
            temp_open_set_element = first_open_set_element;

            // f-score sorting
            while (temp_open_set_element->next != NULL)
            {
                if (neighbour_element->f <= temp_open_set_element->next->f)
                    break;

                temp_open_set_element = temp_open_set_element->next;
            }

            // h-score sorting
            while (temp_open_set_element->next != NULL)
            {
                if (neighbour_element->f < temp_open_set_element->next->f)
                    break; // to account if there are multiple elements with the same f-score -> break as soon as the next one is greater than neighbour f-score (end of the list of the same f-score)

                if (neighbour_element->h <= temp_open_set_element->next->h)
                    break;

                temp_open_set_element = temp_open_set_element->next;
            }

            neighbour_element->next = temp_open_set_element->next;
            temp_open_set_element->next = neighbour_element;
        }
    }

    // Case where all possible tiles were explored but no path has been found
    return UNDEFINED_TILE;
}

// Results :
// omg the added speed of the whole solving algorithm by this tiny change is ridiculous
// solving excecution time decreased by like 20% between the two versions (of course numbers of valid boards stay the same, it's the same computation)