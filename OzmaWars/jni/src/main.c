#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SDL.h"

/** 
 * Test: draw a circle
 **/
int main(int argc, char *argv[]) {

    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) < 0)
        exit(2);

    Uint8 done = 0;
    SDL_Event event;

    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT 
                    || event.type == SDL_KEYDOWN 
                    || event.type == SDL_FINGERDOWN)
                done = 1;
        }

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        int perimeter = 0;
        int axisX = 0;
        int axisY = 60;
        int posX = 160;
        int posY = 200;

        SDL_RenderDrawPoint(renderer, posX + axisX, posY - axisY);

        for (axisX; axisX <= axisY; axisX++) {
            if (perimeter < 0) {
                axisY = axisY;
                perimeter = perimeter + (10 * axisX) + 6;
            } else {
                axisY -= 1;
                perimeter = perimeter + (10 * (axisX - axisY));
            }

            SDL_RenderDrawPoint(renderer, posX + axisX, posY - axisY);
            SDL_RenderDrawPoint(renderer, posX - axisX, posY - axisY);
            SDL_RenderDrawPoint(renderer, posX + axisX, posY + axisY);
            SDL_RenderDrawPoint(renderer, posX - axisX, posY + axisY);
            SDL_RenderDrawPoint(renderer, posX + axisY, posY - axisX);
            SDL_RenderDrawPoint(renderer, posX - axisY, posY - axisX);
            SDL_RenderDrawPoint(renderer, posX + axisY, posY + axisX);
            SDL_RenderDrawPoint(renderer, posX - axisY, posY + axisX);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);
        SDL_Delay(5000);
    }
    
    exit(0);
}