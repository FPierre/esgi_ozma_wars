#include <android/log.h>
#include <math.h>

#include "headers/Meteorite.h"

const double PI = 3.14159265358979323846;

#define LOG_TAG "Meteorite"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

Meteorite::Meteorite() {

}

Meteorite::Meteorite(Sprite _image, int screen_width, int screen_height) : image(_image) {
    this->speed = 10;
    this->size_coeff = 200;

    this->area_limits = { 0, 0, screen_width, screen_height };

    this->launch_sound = Mix_LoadWAV("sounds/meteorite_launch.wav");

    if (this->launch_sound == NULL) {
        LOGI("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

Meteorite::Meteorite(const Meteorite& _meteorite) {
    x = _meteorite.x;
    y = _meteorite.y;
    strength = _meteorite.strength;
    image = _meteorite.image;
    area_limits = _meteorite.area_limits;
    launch_sound = _meteorite.launch_sound;
    speed = _meteorite.speed;
    angle = _meteorite.angle;
}

Meteorite::~Meteorite() {

}

void Meteorite::render(SDL_Renderer *_renderer) {
    this->image.render(this->x, this->y, _renderer, this->size_coeff);
}

void Meteorite::set_destination(int target_x, int target_y) {
    int delta_x = target_x - this->x;
    int delta_y = target_y - this->y;

    double angle = atan2(delta_y, delta_x) * (180.0 / PI);
    this->angle = angle;
    this->image.set_angle(angle);
}

void Meteorite::move() {
    int vx = this->speed * (90 - abs(this->angle)) / 90;
    int vy; // Velocity in y is the difference of speed and vx.

    if (this->angle < 0) {
        vy = -this->speed + abs(vx);
    }
    else {
        vy = this->speed - abs(vx);
    }

    this->x += vx;
    this->y += vy;
}

int Meteorite::get_x() {
    return this->x;
}

void Meteorite::set_x(int _x) {
    this->x = _x;
}

int Meteorite::get_y() {
    return this->y;
}

void Meteorite::set_y(int _y) {
    this->y = _y;
}

int Meteorite::get_strength() {
    return this->strength;
}

// TRUE si le météorite est dans la zone de l'écran
bool Meteorite::in_area_limit() {
    return (this->get_x() >= this->area_limits.x &&
            this->get_x() <= this->area_limits.w &&
            this->get_y() >= this->area_limits.y &&
            this->get_y() <= this->area_limits.h);
}

Sprite Meteorite::get_sprite() {
    return this->image;
}
