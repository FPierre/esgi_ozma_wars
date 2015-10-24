#include "headers/OwnShip.h"

const double PI = 3.14159265358979323846;

OwnShip::OwnShip() : Ship() {

}

OwnShip::OwnShip(int _x, int _y, int _health, Weapon _weapon, Sprite *_sprite) : Ship(_x, _y, _health, _weapon, _sprite) {
    // LOGI("Constructeur");
}

OwnShip::OwnShip(const OwnShip& _ship) {
    // LOGI("Constructeur par copie");

    x = _ship.x;
    y = _ship.y;
    health = _ship.health;
    weapon = _ship.weapon;
    sprite = _ship.sprite;
}

OwnShip::~OwnShip() {

}

void OwnShip::move() {

}
