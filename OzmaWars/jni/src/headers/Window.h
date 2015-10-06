#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"

class Window {
    public:
    int w;
    int h;
    SDL_Window *screen;
    SDL_Renderer *renderer;
    Window();
    Window(SDL_Window *_screen, SDL_Renderer *_renderer);
};

#endif
