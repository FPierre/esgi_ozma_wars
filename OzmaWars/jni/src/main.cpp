#include <android/log.h>
#include <jni.h>
#include "android/sensor.h"
#include "../sdl/src/core/android/SDL_android.h"
#include "SDL.h"

#include "Window.h"

int main(int argc, char *argv[]) {
    SDL_Window *screen;
    SDL_Renderer *renderer;
    Window window(renderer, screen);

    if (SDL_CreateWindowAndRenderer(0, 0, 0, &(window.screen), &renderer) < 0)
        exit(2);

    Uint8 done = 0;
    SDL_Event event;

    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: case SDL_KEYDOWN:
                    done = 1;
                    break;
            }
        }

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 12, 12, 12, 12);
        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    // SDL_DestroyTexture(tex);
    // SDL_DestroyTexture(tex2);

    exit(0);
}
