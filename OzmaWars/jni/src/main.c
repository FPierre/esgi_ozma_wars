#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SDL.h"

typedef struct Weapon Weapon;
struct Weapon {
    int strength;
};

typedef struct {
    int x;
    int y;
    int size;
    int health;
    int max_health;
    Weapon weapons;
    SDL_Rect rectangle;
} Ship;

Ship *init(int x, int y, int size, int max_health) {
    Ship *ship = malloc(sizeof(Ship));
    ship->x = x;
    ship->y = y;
    ship->size = size;
    ship->health = ship->max_health = max_health;
    ship->rectangle.x = ship->x;
    ship->rectangle.y = ship->y;
    ship->rectangle.w = ship->size;
    ship->rectangle.h = ship->size;

    return ship;
}

// void step_ship(Ship *ship);
// void blit_ship(Ship *ship, SDL_Surface *target);
// void kb_control(Ship *player, Uint8 *keys);

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) < 0)
        exit(2);

    Uint8 done = 0;
    SDL_Event event;

    Ship *ship;
    int x = 0;

    while (!done) {
        ship = init(x, 0, 200, 100);

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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    exit(0);
}
