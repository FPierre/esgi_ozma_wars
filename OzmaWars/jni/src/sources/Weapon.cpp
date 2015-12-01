#include <android/log.h>
#include <math.h>

#include "headers/Weapon.h"

const double PI = 3.14159265358979323846;

#define LOG_TAG "Weapon"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

Weapon::Weapon() {

}

Weapon::Weapon(int _strength, Sprite _image, int screen_width, int screen_height) : strength(_strength),
                                                                                    image(_image) {
    this->speed = 10;
    this->size_coeff = 10;
    this->area_limits = { 0, 0, screen_width, screen_height };

    this->launch_sound = Mix_LoadWAV("sounds/missile_launch.wav");

    if (this->launch_sound == NULL) {
        LOGI("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

Weapon::Weapon(const Weapon& _weapon) {
    angle = _weapon.angle;
    area_limits = _weapon.area_limits;
    image = _weapon.image;
    launch_sound = _weapon.launch_sound;
    size_coeff = _weapon.size_coeff;
    speed = _weapon.speed;
    strength = _weapon.strength;
    x = _weapon.x;
    y = _weapon.y;
}

Weapon::~Weapon() {

}

int Weapon::get_x() {
    return this->x;
}

void Weapon::set_x(int _x) {
    this->x = _x;
}

int Weapon::get_y() {
    return this->y;
}

void Weapon::set_y(int _y) {
    this->y = _y;
}

void Weapon::set_speed(int _speed) {
    this->speed = _speed;
}

void Weapon::set_angle(double _angle) {
    this->angle = _angle;
}

int Weapon::get_strength() {
    return this->strength;
}

Sprite Weapon::get_sprite() {
    return this->image;
}

// TRUE si le vaisseau est dans la zone de l'écran
bool Weapon::in_area_limit() {
    return (this->get_x() >= this->area_limits.x &&
            this->get_x() <= this->area_limits.w &&
            this->get_y() >= this->area_limits.y &&
            this->get_y() <= this->area_limits.h);
}

void Weapon::render(SDL_Renderer *_renderer) {
    this->image.render(this->x, this->y, _renderer, this->size_coeff);
}

void Weapon::set_destination(int target_x, int target_y, bool _force_angle) {
    int delta_x = target_x - this->x;
    int delta_y = target_y - this->y;

    double angle = atan2(delta_y, delta_x) * (180.0 / PI);
    this->angle = angle;

    this->image.set_angle(angle);
}

void Weapon::move() {
    int vx = this->speed * (90 - abs(this->angle)) / 90;
    int vy;

    if (this->angle < 0) {
        vy = -this->speed + abs(vx);
    }
    else {
        vy = this->speed - abs(vx);
    }

    this->x += vx;
    this->y += vy;
}
