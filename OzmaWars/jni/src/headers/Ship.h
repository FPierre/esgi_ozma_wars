#ifndef SHIP_H
#define SHIP_H

#include "SDL.h"

#include "Weapon.h"
#include "Sprite.h"

class Ship {
    private:
    int x;
    int y;
    int health;
    Weapon weapon;
    Sprite *image;
    SDL_Rect border_limits;

    public:
    Ship();
    Ship(int _x, int _y, int _health, Weapon _weapon, Sprite *_image, SDL_Rect _border_limits);
    Ship(const Ship& _ship);
    ~Ship();
    void render(SDL_Renderer *_renderer);
    void move(int _x, int _y);
    void fire(int _x, int _y);
};

#endif
