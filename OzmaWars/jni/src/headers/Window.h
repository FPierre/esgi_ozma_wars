#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"

class Window {
    private:
    int w; // Largeur de l'écran
    int h; // Hauteur de l'écran

    public:
    // TODO A passer en private, getter/setter
    SDL_Window *screen;
    // TODO A passer en private, getter/setter
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
