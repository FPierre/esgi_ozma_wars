#include <math.h>

#include "headers/Weapon.h"

const double PI = 3.14159265358979323846;

Weapon::Weapon() {

}

Weapon::Weapon(int _strength, Sprite *_image) : strength(_strength),
                                                image(_image) {

}

Weapon::Weapon(const Weapon& _weapon) {
    strength = _weapon.strength;
    image = _weapon.image;
}

Weapon::~Weapon() {

}

void Weapon::render(SDL_Renderer *_renderer) {
    this->image->render(_renderer);
}

void Weapon::move(int _start_x, int _start_y, int _target_x, int _target_y) {
    double val = 180.0 / PI;
    double diff_x = _target_x - _start_x;
    double diff_y = _target_y - _start_y;
    double length = sqrt(diff_x * diff_x + diff_y * diff_y);
    double angle = atan2(diff_y, diff_x) * val;

    this->image->angle = angle;

    if (this->x < _target_x) {
        this->x += diff_x / 100;
    }

    if (this->y < _target_y) {
        this->y += diff_y / 100;
    }
}
