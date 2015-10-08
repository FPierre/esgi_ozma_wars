#include <android/log.h>
#include <math.h>

#include "headers/Ship.h"

const double PI = 3.14159265358979323846;

#define LOG_TAG "Ship"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

Ship::Ship() {

}

Ship::Ship(int _x, int _y, int _health, Weapon _weapon, Sprite *_image, SDL_Rect _border_limits) : x(_x),
                                                                                                   y(_y),
                                                                                                   health(_health),
                                                                                                   weapon(_weapon),
                                                                                                   image(_image),
                                                                                                   border_limits(_border_limits) {
    this->weapon.x = _x;
    this->weapon.y = _y;
}

Ship::Ship(const Ship& _ship) {
    x = _ship.x;
    y = _ship.y;
    health = _ship.health;
    weapon = _ship.weapon;
    image = _ship.image;
}

Ship::~Ship() {

}

void Ship::render(SDL_Renderer *_renderer) {
    if (this->health > 0) {
        this->image->render(this->x, this->y, _renderer);

        if (this->weapon.x != this->x || this->weapon.y != this->y) {
            this->weapon.render(_renderer);
        }
    }
    else {
        // Sprite d'une explosion
        // Render d'un bonus ici ?
    }
}

void Ship::move(int _x, int _y) {
    double val = 180.0 / PI;
    double diff_x = _x - this->x;
    double diff_y = _y - this->y;
    double length = sqrt(diff_x * diff_x + diff_y * diff_y);
    double angle = atan2(diff_y, diff_x) * val;

    this->image->angle = angle;

    // TODO Gérer la vitesse par ce / 100
    if (this->x < _x) {
        this->x += diff_x / 100;
    }

    if (this->y < _y) {
        this->y += diff_y / 100;
    }

    // if (_x < this->border_limits.x) {
    //     _x = 0;
    // }

    // if (_x > this->border_limits.w) {
    //     _x = this->border_limits.w;
    // }

    // if (_y < this->border_limits.y) {
    //     _y = 0;
    // }

    // if (_y > this->border_limits.h) {
    //     _y = this->border_limits.h;
    // }
}

void Ship::fire(int _x, int _y) {
    this->weapon.move(this->x, this->y, _x, _y);
}
