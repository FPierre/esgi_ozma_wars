#include "Sprite.h"

Sprite::Sprite() {

}

Sprite::Sprite(int _x, int _y, int _w, int _h, double _angle, std::string _path, Rgb& _background) : x(_x),
                                                                                                     y(_y),
                                                                                                     w(_w),
                                                                                                     h(_h),
                                                                                                     angle(_angle),
                                                                                                     background(_background) {
    this->surface = SDL_LoadBMP(_path.c_str());
    SDL_SetColorKey(this->surface, SDL_TRUE, SDL_MapRGB(this->surface->format, this->background.r, this->background.g, this->background.b));
    this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

    SDL_Rect test = { this->x, this->y, this->w, this->h };
    this->image_location = test;

    // this->image_location->x = this->x;
    // this->image_location->y = this->y;
    // this->image_location->w = this->w;
    // this->image_location->h = this->h;
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

void Sprite::render(SDL_Renderer *renderer) {
    SDL_Rect test = { 100, 100, 100, 100 };
    SDL_RenderCopy(renderer, this->texture, &(this->image_location), &test);
}
