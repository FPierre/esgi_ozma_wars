#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"

class Window {
    private:
    int w; // Largeur de l'écran
    int h; // Hauteur de l'écran

    public:
    SDL_Window *screen;
    SDL_Renderer *renderer;
    Window();
    Window(const Window& _window);
    ~Window();
    int get_width();
    void set_width(int _w);
    int get_height();
    void set_height(int _h);
};

#endif
