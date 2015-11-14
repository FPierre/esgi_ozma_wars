#include <android/log.h>
#include <math.h>

#include "headers/Ship.h"

#define LOG_TAG "Ship"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

Ship::Ship() {
    // LOGI("Constructeur trivial");
}

Ship::Ship(int _x, int _y, int _health, Weapon _weapon, Sprite *_image) : x(_x),
                                                                          y(_y),
                                                                          health(_health),
                                                                          weapon(_weapon),
                                                                          image(_image) {
    // LOGI("Constructeur");

    this->length_x = 0;
    this->length_y = 0;
    this->destination_x = 0;
    this->destination_y = 0;
    // TODO Passer les valeurs de l'attribut screen de l'objet Window
    this->area_limits = { 0, 0, 1920, 1080 };

    this->weapon.x = _x;
    this->weapon.y = _y;
}

Ship::Ship(const Ship& _ship) {
    // LOGI("Constructeur par copie");

    x = _ship.x;
    y = _ship.y;
    length_x = _ship.length_x;
    length_y = _ship.length_y;
    destination_x = _ship.destination_x;
    destination_y = _ship.destination_y;
    health = _ship.health;
    weapon = _ship.weapon;
    image = _ship.image;
    area_limits = _ship.area_limits;
    fired_weapons = _ship.fired_weapons;
}

Ship::~Ship() {

}

int Ship::get_health() {
    return this->health;
}

bool Ship::alive() {
    return this->get_health() > 0;
}

void Ship::set_sprite(Sprite *_image) {
    this->image = _image;
}

void Ship::render(SDL_Renderer *_renderer) {
    this->image->render(this->x, this->y, _renderer);

    for (Weapon *fired_weapon : this->fired_weapons) {
        // if (fired_weapon.get_fired() == true) {
        // if (this->weapon.x != this->x || this->weapon.y != this->y) {
            fired_weapon->render(_renderer);
        // }
    }
}
