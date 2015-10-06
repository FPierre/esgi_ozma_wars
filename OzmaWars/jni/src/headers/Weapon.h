#ifndef WEAPON_H
#define WEAPON_H

#include "SDL.h"

#include "Sprite.h"

class Weapon {
    private:
    int strength;

    public:
    Sprite *image;
    int x;
    int y;
    Weapon();
    Weapon(int _strength, Sprite *_image);
    Weapon(const Weapon& _weapon);
    ~Weapon();
    void render(SDL_Renderer *_renderer);
    // TODO Passer en private ? N'est à utiliser que dans le fire de Ship
    void move(int _start_x, int _start_y, int _target_x, int _target_y);
};

#endif
