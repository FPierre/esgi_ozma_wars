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
    Window(const Window& _window);
    ~Window();
};

#endif
