#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"

class Window {
    private:
    int w;
    int h;
    SDL_Renderer *renderer;

    public:
    SDL_Window *screen;
    Window(SDL_Renderer *_renderer, SDL_Window *_screen);
};

#endif
