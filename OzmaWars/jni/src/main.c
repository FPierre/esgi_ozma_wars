#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "SDL.h"
#include "math.h"
#include "weapon.h"
#include "ship.h"

#define PI 3.14159265

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip) {
    SDL_Rect dst = { x, y, clip->w, clip->h };

    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_RenderPresent(ren);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) < 0)
        exit(2);

    Uint8 done = 0;
    SDL_Event event;

    Weapon *laser_canon = weapon_init(1);

    Ship *ship = ship_init(400, 400, 200, 100, *laser_canon);
    Ship *enemy_ship = ship_init(10, 10, 100, 100, *laser_canon);

    SDL_Surface *pSprite = SDL_LoadBMP("spritesheets/ship.bmp");
    SDL_SetColorKey(pSprite, SDL_TRUE, SDL_MapRGB(pSprite->format, 255, 0, 255));
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, pSprite);
    SDL_Rect srcrect = { 41, 42, 40, 45 };


    // TEST MISSILE

    double val = 180.0 / PI;

    SDL_Surface *pSprite2 = SDL_LoadBMP("spritesheets/projectile.bmp");
    SDL_SetColorKey(pSprite2, SDL_TRUE, SDL_MapRGB(pSprite2->format, 0, 255, 255));
    SDL_Texture *tex2 = SDL_CreateTextureFromSurface(renderer, pSprite2);
    SDL_Rect srcrect2 = { 55, 390, 50, 20 };

    int start_x = 10;
    int start_y = 10;

    SDL_Rect missile = { start_x, start_y, 100, 60 };

    int end_x = 400;
    int end_y = 400;

    int diff_x = end_x - start_x;
    int diff_y = end_y - start_y;

    int length = sqrt(diff_x * diff_x + diff_y * diff_y);
    double angle = atan2(diff_y, diff_x) * val;

    while (!done) {


        missile.x += length / 100;
        missile.y += length / 100;


        // enemy_ship->rectangle.x++;

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

        SDL_RenderCopy(renderer, tex, &srcrect, &(ship->rectangle));

        // SDL_RenderCopy(renderer, tex2, &srcrect2, &(enemy_ship->rectangle));

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
        SDL_RenderFillRect(renderer, &(enemy_ship->rectangle));


        SDL_RenderCopyEx(renderer, tex2, &srcrect2, &missile, angle, NULL, SDL_FLIP_NONE);

        // SDL_RenderCopy(renderer, tex2, &srcrect2, &missile);
        // SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
        // SDL_RenderFillRect(renderer, &missile);


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }



// int iW = 120 / 3, iH = 50;

// SDL_Rect clips[3];

// int i;
// for (i = 0; i < 2; ++i) {
//     // clips[i].x = i / 2 * iW;
//     // clips[i].y = i % 2 * iH;
//     // clips[i].w = iW;
//     // clips[i].h = iH;
//     clips[i].x = 0;
//     clips[i].y = 0;
//     clips[i].w = 40;
//     clips[i].h = 40;
// }

// //Specify a default clip to start with
// int useClip = 0;

//         SDL_Surface *pSprite = SDL_LoadBMP("image.bmp");

//         SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, pSprite);

//         renderTexture(tex, renderer, 200, 200, &clips[useClip]);




    SDL_DestroyTexture(tex);
    // SDL_DestroyTexture(tex2);

    exit(0);
}
