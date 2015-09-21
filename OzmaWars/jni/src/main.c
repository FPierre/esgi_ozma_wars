#include <stdlib.h>
#include <stdio.h>
#include <android/log.h>
#include "android/sensor.h"
#include "../SDL/src/core/android/SDL_android.h"
#include "SDL.h"

#include "math.h"
#include "sprite.h"
#include "weapon.h"
#include "ship.h"

#define  PI         3.14159265
#define  LOG_TAG    "MAIN NATIVE"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


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

    // Initialisation Weapon

    RGB blue_background = { 0, 255, 255 };
    Sprite *missile_image = sprite_init(renderer, "spritesheets/projectile.bmp", blue_background, 55, 390, 50, 20);

    Weapon *canon = weapon_init(100, 60, 1, 1, missile_image);

    // Initialisation Ship

    RGB pink_background = { 255, 0, 255 };
    Sprite *ship_image = sprite_init(renderer, "spritesheets/ship.bmp", pink_background, 41, 42, 40, 45);
    Sprite *enemy_ship_image = sprite_init(renderer, "spritesheets/ship.bmp", pink_background, 155, 303, 30, 28);

    float ship_x = 400;
    float ship_y = 400;
    // float ship_z = 1;
    int ship_size = 200;

    Ship *ship = ship_init(ship_x, ship_y, ship_size, ship_size, 0.0, 100, ship_image, canon);
    Ship *enemy_ship = ship_init(10, 10, 100, 100, 180.0, 100, enemy_ship_image, canon);

    // TEST MISSILE

    // double val = 180.0 / PI;

    // SDL_Surface *pSprite2 = SDL_LoadBMP("spritesheets/projectile.bmp");
    // SDL_SetColorKey(pSprite2, SDL_TRUE, SDL_MapRGB(pSprite2->format, 0, 255, 255));
    // SDL_Texture *tex2 = SDL_CreateTextureFromSurface(renderer, pSprite2);
    // SDL_Rect srcrect2 = { 55, 390, 50, 20 };

    // int start_x = 10;
    // int start_y = 10;

    // SDL_Rect missile = { start_x, start_y, 100, 60 };

    // int end_x = 400;
    // int end_y = 400;

    // int diff_x = end_x - start_x;
    // int diff_y = end_y - start_y;

    // int length = sqrt(diff_x * diff_x + diff_y * diff_y);
    // double angle = atan2(diff_y, diff_x) * val;

    int first_fire = 1;

    while (!done) {

        if (first_fire == 1) {


            first_fire = 0;
        }


        // missile.x += length / 100;
        // missile.y += length / 100;

        // enemy_ship->rectangle.x++;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = 1;
                    break;

                case SDL_MOUSEMOTION:
                    // ship->rectangle.x += 2;
                    break;
            }
        }


        SDL_RenderClear(renderer);

        // Render de débug du missile
        // sprite_render(renderer, missile_image);

        weapon_render(renderer, canon);

        float accelValues[3];
        Android_JNI_GetAccelerometerValues(accelValues);
        int i = 0;
        char values[30];

        for(i = 0 ; i < 3 ; i++) {
            switch(i) {
                case 0: 
                    sprintf(values, "value X %f", accelValues[i]);
                    ship_x += (4 * accelValues[i]);
                    break;

                case 1: 
                    sprintf(values, "value Y %f", accelValues[i]);
                    ship_y += (4 * accelValues[i]);
                    break;

                case 2: 
                    sprintf(values, "value Z %f", accelValues[i]);
                    break;
            }
            LOGD("%s", values);
            memset(values, 0, 30 * (sizeof values[0]));
        }

        // Valeurs de l'accelerometre x, y et z
        // float accelValues[3];
        // Android_JNI_GetAccelerometerValues(accelValues);

        // ship_x = ship_x + accelValues[0];
        // ship_y = ship_y + accelValues[1];
        // // z += accelValues[2];

        // LOGD("Values: X = %.2f", ship_x);
        // LOGD("Values: Y = %.2f", ship_y);
        // // LOGD("Values: Z = %.2f", z);

        Ship *ship = ship_init(ship_x, ship_y, ship_size, ship_size, 0.0, 100, ship_image, canon);

        ship_render(renderer, ship);
        ship_render(renderer, enemy_ship);

        // // SDL_RenderCopyEx(renderer, tex2, &srcrect2, &missile, angle, NULL, SDL_FLIP_NONE);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    // SDL_DestroyTexture(tex);
    // SDL_DestroyTexture(tex2);

    exit(0);
}
