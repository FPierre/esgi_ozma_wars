#include <android/log.h>
#include <jni.h>
#include "android/sensor.h"
#include "../sdl/src/core/android/SDL_android.h"
#include "SDL.h"
#include <string>

#include "Window.h"
#include "Rgb.h"
#include "Sprite.h"
#include "Ship.h"

int main(int argc, char *argv[]) {
    SDL_Window *screen;
    SDL_Renderer *renderer;
    Window window(screen, renderer);

    if (SDL_CreateWindowAndRenderer(0, 0, 0, &(window.screen), &(window.renderer)) < 0)
    // if (SDL_CreateWindowAndRenderer(0, 0, 0, &screen, &renderer) < 0)
        exit(2);

    Uint8 done = 0;
    SDL_Event event;

    Rgb pink_background(255, 0, 255);
    Sprite ship_image(41, 42, 40, 45, 0.0, "spritesheets/ship.bmp", pink_background);
    // Ship ship(0, 0, 100, ship_image);

    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: case SDL_KEYDOWN:
                    done = 1;
                    break;
            }
        }

        SDL_RenderClear(window.renderer);

        // ship.render(window.renderer);

        SDL_SetRenderDrawColor(window.renderer, 35, 226, 35, SDL_ALPHA_OPAQUE);
        // SDL_SetRenderDrawColor(window.renderer, 226, 35, 35, SDL_ALPHA_OPAQUE);
        SDL_RenderPresent(window.renderer);

        SDL_Delay(10);
    }

    // SDL_DestroyTexture(tex);
    // SDL_DestroyTexture(tex2);

    exit(0);
}
