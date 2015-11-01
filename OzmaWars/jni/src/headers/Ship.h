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
    int status;
    Sprite *image;
    SDL_Rect area_limits;

    public:
    Weapon weapon;
    Ship();
    Ship(int _x, int _y, int _health, int _status, Weapon _weapon, Sprite *_image);
    Ship(const Ship& _ship);
    ~Ship();
    int get_x();
    int get_y();
    Sprite *get_sprite();
    void set_sprite(Sprite *_image);
    int get_health();
    void set_health(int _health);
    int get_status();
    void set_status(int _status);
    bool alive();
    void render(SDL_Renderer *_renderer, Sprite *_sprite);
    void fire(int _x, int _y);
    virtual void move() = 0;
};

#endif
