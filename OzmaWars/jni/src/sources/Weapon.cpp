#include <math.h>

#include "headers/Weapon.h"

const double PI = 3.14159265358979323846;

Weapon::Weapon() {

}

Weapon::Weapon(int _strength, Sprite *_image) : strength(_strength),
                                                image(_image) {
    // this->x = 0;
    // this->y = 0;
    this->length_x = 0;
    this->length_y = 0;
    this->destination_x = 0;
    this->destination_y = 0;
}

Weapon::Weapon(const Weapon& _weapon) {
    x = _weapon.x;
    y = _weapon.y;
    length_x = _weapon.length_x;
    length_y = _weapon.length_y;
    destination_x = _weapon.destination_x;
    destination_y = _weapon.destination_y;
    strength = _weapon.strength;
    image = _weapon.image;
}

Weapon::~Weapon() {

}

void Weapon::render(SDL_Renderer *_renderer) {
    this->image->render(this->x, this->y, _renderer);
}

void Weapon::set_destination(int _x, int _y) {
    int diff_x = _x - this->x;
    int diff_y = _y - this->y;
    double angle = atan2(diff_x, diff_y) * (180.0 / PI);

    // LOGI("this->x : %d", this->x);
    // LOGI("this->y : %d", this->y);
    // LOGI("_x : %d", _x);
    // LOGI("_y : %d", _y);
    // LOGI("diff_x : %d", diff_x);
    // LOGI("diff_y : %d", diff_y);
    // LOGI("Angle : %f", angle);

    // TODO Faire des struct Target (avec x et y) pour gérer les points
    this->destination_x = _x;
    this->destination_y = _y;
    this->length_x = diff_x;
    this->length_y = diff_y;

    this->image->set_angle(angle);
}

void Weapon::move() {
    // LOGI("this->x : %d", this->x);
    // LOGI("this->y : %d", this->y);
    // LOGI("this->destination_x : %d", this->destination_x);
    // LOGI("this->destination_y : %d", this->destination_y);


    // Le missile ne doit pas s'arreter s'il atteint sa "destination"
    // S'il ne touche pas un vaisseau, il sort de l'écran
    // TODO Gérer la vitesse par / 50
    // if (this->x < this->destination_x) {
        this->x += this->length_x / 50;
    // }

    // if (this->y < this->destination_y) {
        this->y += this->length_y / 50;
    // }
}
