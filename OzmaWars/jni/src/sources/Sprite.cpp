#include <android/log.h>

#include "headers/Sprite.h"

#define LOG_TAG "Sprite"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

Sprite::Sprite() {

}

Sprite::Sprite(int _x, int _y, int _w, int _h, double _angle, std::string _path, Rgb& _background, SDL_Renderer *_renderer) : x(_x),
                                                                                                                              y(_y),
                                                                                                                              w(_w),
                                                                                                                              h(_h),
                                                                                                                              angle(_angle),
                                                                                                                              background(_background) {
    this->surface = SDL_LoadBMP(_path.c_str());

    if (this->surface == NULL) {
        LOGI("Sprite non trouve");
        LOGI("%s\n", SDL_GetError());
        exit(0);
    }

    SDL_SetColorKey(this->surface, SDL_TRUE, SDL_MapRGB(this->surface->format, this->background.r, this->background.g, this->background.b));

    this->texture = SDL_CreateTextureFromSurface(_renderer, this->surface);
    this->image_location = { this->x, this->y, this->w, this->h };
}

Sprite::Sprite(const Sprite& _sprite) {
    x = _sprite.x;
    y = _sprite.y;
    w = _sprite.w;
    h = _sprite.h;
    angle = _sprite.angle;
    background = _sprite.background;
    surface = _sprite.surface;
    texture = _sprite.texture;
    image_location = _sprite.image_location;
}

Sprite::~Sprite() {
    // SDL_DestroyTexture(this->texture);
}

int Sprite::get_width() {
    return this->w;
}

int Sprite::get_height() {
    return this->h;
}

double Sprite::get_angle() {
    return this->angle;
}

void Sprite::set_angle(double _angle) {
    this->angle = _angle;
}

void Sprite::render(int _x, int _y, SDL_Renderer *_renderer) {
    SDL_Rect surface = { _x, _y, this->w * 2 + 10, this->h * 2 + 10 };
    SDL_RenderCopyEx(_renderer, this->texture, &(this->image_location), &surface, this->angle, NULL, SDL_FLIP_NONE);
}
