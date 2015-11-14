#ifndef WEAPON_H
#define WEAPON_H

#include "SDL.h"
#include "SDL_mixer.h"

#include "Sprite.h"

class Weapon {
    private:
    int strength;
    bool fired;

    public:
    int x;
    int y;
    int length_x;
    int length_y;
    int destination_x;
    int destination_y;
    Sprite *image;
    Mix_Chunk *launch_sound;
    Weapon();
    Weapon(int _strength, Sprite *_image);
    Weapon(const Weapon& _weapon);
    ~Weapon();
    void set_fired(bool _fired);
    bool get_fired();
    void render(SDL_Renderer *_renderer);
    void set_destination(int _x, int _y);
    int get_x();
    int get_y();
    Sprite *get_sprite();
    // TODO Passer en private ? N'est à utiliser que dans le fire de Ship
    void move();
};

#endif
