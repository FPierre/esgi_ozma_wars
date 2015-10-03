#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "SDL.h"

#include "Rgb.h"

class Sprite {
    private:
    int x;
    int y;
    int w;
    int h;
    double angle;
    Rgb background;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect image_location;
    SDL_Renderer *renderer;

    public:
    Sprite();
    Sprite(int _x, int _y, int _w, int _h, double _angle, std::string _path, Rgb& _background);
    Sprite(const Sprite& _sprite);
    ~Sprite();
    void render(SDL_Renderer *renderer);
};

#endif
