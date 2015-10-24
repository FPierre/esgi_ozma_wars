#include "android/sensor.h"
#include "../sdl/src/core/android/SDL_android.h"

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
    float accelerometer_values[3];
    Android_JNI_GetAccelerometerValues(accelerometer_values);

    float tmp_x_value = this->x + (20 * accelerometer_values[0]);
    float tmp_y_value = this->y + (20 * accelerometer_values[1]);

    // TODO Passer cette partie dans constructeur (ce calcul n'est pas a faire ici)
    int ship_width = this->sprite->get_width() * 2;
    int ship_height = this->sprite->get_height() * 2;

    if (tmp_x_value >= this->area_limits.x && tmp_x_value <= (this->area_limits.w - ship_width)) {
        this->x = tmp_x_value;
    }

    if (tmp_y_value >= this->area_limits.y && tmp_y_value <= (this->area_limits.h - ship_height)) {
        this->y = tmp_y_value;
    }
}
