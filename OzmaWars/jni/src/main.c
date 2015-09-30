#include <stdlib.h>
#include <stdio.h>
#include <android/log.h>
#include "android/sensor.h"
#include "../sdl/src/core/android/SDL_android.h"
#include "SDL.h"

#include "sprite.h"
#include "weapon.h"
#include "ship.h"

#define  LOG_TAG    "MAIN NATIVE"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

int main(int argc, char *argv[]) {
    srand(time(NULL));

    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) < 0)
        exit(2);

    Uint8 done = 0;
    SDL_Event event;

    // Initialisation Weapon

    RGB blue_background = { 0, 255, 255 };
    Sprite *missile_image = sprite_init(renderer, "spritesheets/projectile.bmp", blue_background, 55, 390, 50, 20);

    Weapon *canon = weapon_init(100, 60, 0.0, 1, 1, missile_image);

    // Initialisation Ship

    RGB pink_background = { 255, 0, 255 };
    Sprite *ship_image = sprite_init(renderer, "spritesheets/ship.bmp", pink_background, 41, 42, 40, 45);
    Sprite *enemy_ship_image = sprite_init(renderer, "spritesheets/ship.bmp", pink_background, 155, 303, 30, 28);

    float ship_x = 700;
    float ship_y = 400;
    int ship_size = 150;

    Ship *ship = ship_init(ship_x, ship_y, ship_size, ship_size, 0.0, 100, ship_image, canon);
    Ship *enemy_ship = ship_init(10, 10, 100, 100, 180.0, 100, enemy_ship_image, canon);

    // TEST MISSILE

    // struct Target ride[2];

    // Target a = { 200, 300 };
    // Target b = { 300, 400 };

    // ride[1] = a;
    // ride[2] = b;

    // int i, j;

    // for (i = 0; i < 1; i++) {
    //     for (j = 0; j < 1; j++) {
    //         ride[i].p[j] = 0;
    //         ride[i].v[j] = 0;
    //     }
    // }

    ship_fire(enemy_ship, ship);

    ship_set_ride(enemy_ship, 100, 700);

    while (!done) {
        weapon_move(enemy_ship->weapon);
        ship_move(enemy_ship);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = 1;
                    break;

                case SDL_MOUSEMOTION:
                    // ship->body.x += 2;
                    break;
            }
        }


        SDL_RenderClear(renderer);

        // Render de débug du missile
        // sprite_render(renderer, missile_image);

        weapon_render(renderer, canon);

        // Valeurs de l'accelerometre

        float accelValues[3];
        Android_JNI_GetAccelerometerValues(accelValues);

        ship_x += (20 * accelValues[0]);
        ship_y += (20 * accelValues[1]);

        // Mouvement du vaisseau

        if (ship->body.x > ship_x) {
            sprite_position(ship_image, 0, 42);
        } else if(ship->body.x < ship_x) {
            sprite_position(ship_image, 82, 42);
        } else {
            sprite_position(ship_image, 41, 42);
        }

        ship->image = ship_image;

        ship->body.x = ship_x;
        ship->body.y = ship_y;

        // Affichage des éléments

        ship_render(renderer, ship);
        ship_render(renderer, enemy_ship);

        SDL_SetRenderDrawColor(renderer, 12, 12, 12, 12);
        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    // SDL_DestroyTexture(tex);
    // SDL_DestroyTexture(tex2);

    exit(0);
}
