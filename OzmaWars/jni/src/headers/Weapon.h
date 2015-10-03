#ifndef WEAPON_H
#define WEAPON_H

#include "SDL.h"

#include "Sprite.h"

class Weapon {
    private:
    int strength;
    Sprite *image;

    public:
    Weapon();
    Weapon(int _strength, Sprite *_image);
    Weapon(const Weapon& _weapon);
    ~Weapon();
    void render(SDL_Renderer *_renderer);
    void move(int _x, int _y);
};

#endif
