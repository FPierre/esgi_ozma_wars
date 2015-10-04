#include "headers/Sprite.h"

Sprite::Sprite() {

}

Sprite::Sprite(int _x, int _y, int _w, int _h, double _angle, std::string _path, Rgb& _background, SDL_Renderer *_renderer) : x(_x),
                                                                                                                              y(_y),
                                                                                                                              w(_w),
                                                                                                                              h(_h),
                                                                                                                              angle(_angle),
                                                                                                                              background(_background) {
    this->surface = SDL_LoadBMP(_path.c_str());
    SDL_SetColorKey(this->surface, SDL_TRUE, SDL_MapRGB(this->surface->format, this->background.r, this->background.g, this->background.b));
    this->texture = SDL_CreateTextureFromSurface(_renderer, this->surface);

    SDL_Rect location = { this->x, this->y, this->w, this->h };
    this->image_location = location;
}

Sprite::Sprite(const Sprite& _sprite) {
    x = _sprite.x;
    y = _sprite.y;
    w = _sprite.w;
    h = _sprite.h;
    angle = _sprite.angle;
    background = _sprite.background;
}

Sprite::~Sprite() {

}

void Sprite::render(SDL_Renderer *_renderer) {
    SDL_Rect test = { 100, 100, 100, 100 };
    SDL_RenderCopyEx(_renderer, this->texture, &(this->image_location), &test, this->angle, NULL, SDL_FLIP_NONE);
}
