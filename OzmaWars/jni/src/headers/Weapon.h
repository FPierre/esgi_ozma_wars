#ifndef WEAPON_H
#define WEAPON_H

#include "SDL.h"

#include "Sprite.h"

class Weapon {
    private:
    int strength;

    public:
    int x;
    int y;
    int length_x;
    int length_y;
    int destination_x;
    int destination_y;
    Sprite *sprite;
    Weapon();
    Weapon(int _strength, Sprite *_sprite);
    Weapon(const Weapon& _weapon);
    ~Weapon();
    void render(SDL_Renderer *_renderer);
    void set_destination(int _x, int _y);
    // TODO Passer en private ? N'est à utiliser que dans le fire de Ship
    void move();
};

#endif
