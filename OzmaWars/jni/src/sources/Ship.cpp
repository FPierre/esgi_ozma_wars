#include <math.h>

#include "headers/Ship.h"

const double PI = 3.14159265358979323846;

Ship::Ship() {

}

Ship::Ship(int _x, int _y, int _health, Weapon *_weapon, Sprite *_image) : x(_x),
                                                                           y(_y),
                                                                           health(_health),
                                                                           weapon(_weapon),
                                                                           image(_image) {
    this->weapon->x = _x;
    this->weapon->y = _y;
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

    if (this->x < _x) {
        this->x += diff_x / 100;
    }

    if (this->y < _y) {
        this->y += diff_y / 100;
    }
}

void Ship::fire(int _x, int _y) {
    this->weapon->move(this->x, this->y, _x, _y);
}
