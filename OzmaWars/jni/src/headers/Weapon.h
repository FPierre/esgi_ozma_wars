#ifndef WEAPON_H
#define WEAPON_H

#include "SDL.h"
#include "SDL_mixer.h"

#include "Sprite.h"

class Weapon {
    private:
    int x;
    int y;
    int strength;
    int speed;
    double angle;
    int size_coeff;

    public:
    Sprite image;
    Mix_Chunk *launch_sound;
    SDL_Rect area_limits;  // Zone de laquelle le missile est détruit de la mémoire s'il sort
    Weapon();
    Weapon(int _strength, Sprite _image, int screen_width, int screen_height);
    Weapon(const Weapon& _weapon);
    ~Weapon();
    void set_speed(int _speed);
    void set_angle(double _angle);
    void render(SDL_Renderer *_renderer);
    void set_destination(int target_x, int target_y, bool _force_angle = false);
    int get_x();
    void set_x(int _x);
    int get_y();
    void set_y(int _y);
    int get_strength();
    bool in_area_limit();
    Sprite get_sprite();
    void move();
};

#endif
