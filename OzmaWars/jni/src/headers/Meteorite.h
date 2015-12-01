#ifndef METEORITE_H
#define METEORITE_H

#include "SDL.h"
#include "SDL_mixer.h"

#include "Sprite.h"

class Meteorite {
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
    SDL_Rect area_limits;
    Meteorite();
    Meteorite(Sprite _image, int screen_width, int screen_height);
    Meteorite(const Meteorite& _meteorite);
    ~Meteorite();
    void render(SDL_Renderer *_renderer);
    void set_destination(int target_x, int target_y);
    void move();
    int get_x();
    void set_x(int _x);
    int get_y();
    void set_y(int _y);
    int get_strength();
    bool in_area_limit();
    Sprite get_sprite();
};

#endif
