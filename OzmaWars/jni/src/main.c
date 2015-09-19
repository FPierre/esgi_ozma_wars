#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "weapon.h"
#include "ship.h"

#include "SDL.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));

    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) < 0)
        exit(2);

    Uint8 done = 0;
    SDL_Event event;

    Ship *ship = init_ship(400, 400, 200, 100);
    Ship *enemy_ship = init_ship(0, 100, 100, 100);

    while (!done) {
        enemy_ship->rectangle.x += 2;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = 1;
                    break;

                case SDL_MOUSEMOTION:
                    ship->rectangle.x += 2;
                    break;
            }
        }

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &(ship->rectangle));

        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
        SDL_RenderFillRect(renderer, &(enemy_ship->rectangle));

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    exit(0);
}
