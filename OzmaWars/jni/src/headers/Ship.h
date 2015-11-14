#ifndef SHIP_H
#define SHIP_H

#include <vector>
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
    Sprite *image;
    SDL_Rect area_limits;

    public:
    std::vector<Weapon*> fired_weapons;
    Weapon weapon;
    Ship();
    Ship(int _x, int _y, int _health, Weapon _weapon, Sprite *_image);
    Ship(const Ship& _ship);
    ~Ship();
    void set_sprite(Sprite *_image);
    int get_health();
    bool alive();
    void render(SDL_Renderer *_renderer);
    virtual void move() = 0;
};

#endif
