#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define EXIT_IF(condition, msg)                     \
    do                                              \
    {                                               \
        if ((condition))                            \
        {                                           \
            SDL_Log(msg " > %s\n", SDL_GetError()); \
            exit(EXIT_FAILURE);                     \
        }                                           \
    } while (0)

#define SET_COL(r, g, b) EXIT_IF(SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE) != 0, "Erreur set color")

#define FPS 60
const unsigned int ms_allowed_in_one_frame = 1000 / FPS;

void SDL_LimitFPS(unsigned int frame_start_time);

int main(int argc, char **argv)
{
    system("cls");
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    EXIT_IF(SDL_Init(SDL_INIT_VIDEO) != 0, "Erreur : Initialisation SDL");

    window = SDL_CreateWindow("Première fenêtre SDL2", 100, 100, 800, 500, SDL_WINDOW_SHOWN);
    EXIT_IF(window == NULL, "Erreur : Creation fenetre");

    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect rectangle = {.x = 50, .y = 50, .w = 50, .h = 50};

    bool run = true;
    SDL_Event event;

    unsigned int frame_start_time = 0;

    while (run)
    {
        frame_start_time = SDL_GetTicks();
        // events and logic
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                run = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {

                case SDLK_d:
                    printf("Vous avez appuye sur D\n");
                    rectangle.x++;
                    break;

                case SDLK_q:
                    printf("Vous avez appuye sur Q\n");
                    rectangle.x--;
                    break;
                }
                break;

            case SDL_MOUSEMOTION:
                rectangle.x = event.motion.x;
                rectangle.y = event.motion.y;
                break;

            default:
                break;
            }
        }

        // draw
        SET_COL(0, 0, 0);
        EXIT_IF(SDL_RenderClear(renderer) != 0, "Erreur clear rendu");

        SET_COL(200, 0, 0);
        EXIT_IF(SDL_RenderDrawRect(renderer, &rectangle) != 0, "Erreur dessin rectangle");

        SDL_RenderPresent(renderer);
        SDL_LimitFPS(frame_start_time);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void SDL_LimitFPS(unsigned int frame_start_time)
{
    unsigned int current_time = SDL_GetTicks();

    if (current_time < frame_start_time + ms_allowed_in_one_frame)
        SDL_Delay(frame_start_time + ms_allowed_in_one_frame - current_time);
}