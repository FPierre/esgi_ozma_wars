#ifndef SHIP_H
#define SHIP_H

#include "SDL.h"

#include "Weapon.h"
#include "Sprite.h"

// TODO Transformer en virtuelle pure ?
class Ship {
    protected:
    int x;
    int y;
    int length_x;
    int length_y;
    int destination_x;
    int destination_y;
    int health;
    Sprite *sprite;
    SDL_Rect area_limits;

    public:
    Weapon weapon;
    Ship();
    Ship(int _x, int _y, int _health, Weapon _weapon, Sprite *_image);
    Ship(const Ship& _ship);
    ~Ship();
    void render(SDL_Renderer *_renderer);
    void fire(int _x, int _y);
    virtual void move() = 0;
};

#endif
