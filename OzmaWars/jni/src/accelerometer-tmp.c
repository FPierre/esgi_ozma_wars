#include <stdlib.h>
#include <stdio.h>
#include <android/log.h>
#include "android/sensor.h"

#include "SDL.h"

#define  LOG_TAG    "MAIN NATIVE"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

int main(int argc, char *argv[]) {

    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) < 0)
        exit(2);

    Uint8 done = 0;
    SDL_Event event;

    float x = 120;
    float y = 250;
    float z = 1;
    int size = 80;

    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN)
                done = 1;
        }

        float accelValues[3];
        Android_JNI_GetAccelerometerValues(accelValues);

        x += accelValues[0];
        y += accelValues[1];
        z += accelValues[2];

        LOGD("Values: X = %.2f", x);
        LOGD("Values: Y = %.2f", y);
        LOGD("Values: Z = %.2f", z);

        SDL_Rect rect = { x, y, size, size };

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        SDL_RenderPresent(renderer);
        SDL_Delay(200);
    }
    
    exit(0);
}