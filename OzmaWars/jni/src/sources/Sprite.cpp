#include <android/log.h>

#include "headers/Sprite.h"

#define LOG_TAG "Sprite"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

Sprite::Sprite() {
    // LOGI("Constructeur trivial");
}

Sprite::Sprite(int _x, int _y, int _w, int _h, double _angle, std::string _path, Rgb& _background, SDL_Renderer *_renderer) : x(_x),
                                                                                                                              y(_y),
                                                                                                                              w(_w),
                                                                                                                              h(_h),
                                                                                                                              angle(_angle),
                                                                                                                              background(_background) {
    // LOGI("Constructeur");
    this->surface = SDL_LoadBMP(_path.c_str());

    if (this->surface == NULL) {
        LOGI("Sprite non trouve");
        LOGI("%s\n", SDL_GetError());
        exit(0);
    }

    SDL_SetColorKey(this->surface, SDL_TRUE, SDL_MapRGB(this->surface->format, this->background.r, this->background.g, this->background.b));

    this->texture = SDL_CreateTextureFromSurface(_renderer, this->surface);
    this->image_location = { this->x, this->y, this->w, this->h };;
}

Sprite::Sprite(const Sprite& _sprite) {
    // LOGI("Constructeur par copie");

    x = _sprite.x;
    y = _sprite.y;
    w = _sprite.w;
    h = _sprite.h;
    angle = _sprite.angle;
    background = _sprite.background;
}

Sprite::~Sprite() {

}

void Sprite::set_angle(double _angle) {
    this->angle = _angle;
}

void Sprite::render(int _x, int _y, SDL_Renderer *_renderer) {
    SDL_Rect test = { _x, _y, 100, 100 };
    SDL_RenderCopyEx(_renderer, this->texture, &(this->image_location), &test, this->angle, NULL, SDL_FLIP_NONE);
}
