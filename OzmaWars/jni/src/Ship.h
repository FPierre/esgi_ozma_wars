#ifndef SHIP_H
#define SHIP_H

#include "SDL.h"

#include "Sprite.h"

class Ship {
    private:
    int x;
    int y;
    int health;
    Sprite image;

    public:
    Ship();
    Ship(int _x, int _y, int _health, Sprite& _image);
    Ship(const Ship& _ship);
    ~Ship();
    void render(SDL_Renderer *renderer);
};

#endif
