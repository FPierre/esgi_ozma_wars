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
    // this->length_x = 0;
    // this->length_y = 0;
    // this->destination_x = 0;
    // this->destination_y = 0;
    this->speed = 10;

    this->area_limits = { 0, 0, screen_width, screen_height };

    this->launch_sound = Mix_LoadWAV("sounds/missile_launch.wav");

    if (this->launch_sound == NULL) {
        LOGI("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

Weapon::Weapon(const Weapon& _weapon) {
    x = _weapon.x;
    y = _weapon.y;
    // length_x = _weapon.length_x;
    // length_y = _weapon.length_y;
    // destination_x = _weapon.destination_x;
    // destination_y = _weapon.destination_y;
    strength = _weapon.strength;
    image = _weapon.image;
    area_limits = _weapon.area_limits;
    launch_sound = _weapon.launch_sound;

    // TEST
    speed = _weapon.speed;
    angle = _weapon.angle;
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

bool Weapon::in_area_limit() {
    return (this->get_x() >= this->area_limits.x &&
            this->get_x() <= this->area_limits.w &&
            this->get_y() >= this->area_limits.y &&
            this->get_y() <= this->area_limits.h);
}

Sprite Weapon::get_sprite() {
    return this->image;
}

void Weapon::render(SDL_Renderer *_renderer) {
    this->image.render(this->x, this->y, _renderer);
}

void Weapon::set_destination(int target_x, int target_y, bool _force_angle) {
    int delta_x = target_x - this->x;
    int delta_y = target_y - this->y;

    // if (!_force_angle) {
    //     double angle = atan2(diff_x, diff_y) * (180.0 / PI);
    //     this->image.set_angle(angle);
    // }

    // LOGI("this->x : %d", this->x);
    // LOGI("this->y : %d", this->y);
    // LOGI("_x : %d", _x);
    // LOGI("_y : %d", _y);
    // LOGI("diff_x : %d", diff_x);
    // LOGI("diff_y : %d", diff_y);
    // LOGI("Angle : %f", angle);

    // this->length = sqrt(delta_x * delta_x + delta_y * delta_y);

    // double target_angle = atan2(target_y - this->y, target_x - this->x);
    // this->target_angle = target_angle;

    double angle = atan2(delta_y, delta_x) * (180.0 / PI);
    this->angle = angle;
    this->image.set_angle(angle);

    // LOGI("this->angle : %f", this->angle);

    // this->destination_x = _x;
    // this->destination_y = _y;
    // this->length_x = diff_x;
    // this->length_y = diff_y;
}

void Weapon::move() {
    // LOGI("this->angle : %f", this->angle);
    // LOGI("this->x : %d", this->x);
    // LOGI("this->y : %d", this->y);

    int vx = this->speed * (90 - abs(this->angle)) / 90;
    int vy; // Velocity in y is the difference of speed and vx.

    if (this->angle < 0) {
        // Going upwards
        vy = -this->speed + abs(vx);
    }
    else {
        // Going downwards
        vy = this->speed - abs(vx);
    }

    // LOGI("speed : %d", this->speed);
    // LOGI("AVANT this->y : %d", this->y);
    // LOGI("vy : %d", vy);

    this->x += vx;
    this->y += vy;

    // LOGI("APRES this->y : %d", this->y);

    // this->x += 1 * cos(this->angle);
    // this->y += 1 * sin(this->angle);

    // LOGI("-spedd : %d", -this->speed);
    // LOGI("this->y : %d", this->y);

    // Le missile ne doit pas s'arreter s'il atteint sa "destination"
    // S'il ne touche pas un vaisseau, il sort de l'écran
    // if (this->x < this->destination_x) {
        // this->x += this->length_x / 120;
    // if (this->x < this->destination_x) {
    //     this->x += 5;
    // }
    // else {
    //     this->x -= 5;
    // }

    // if (this->y < this->destination_y) {
        // this->y += this->length_y / 120;
    // if (this->y < this->destination_y) {
    //     this->y += 5;
    // }
    // else {
    //     this->y -= 5;
    // }
}
