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

Ship::Ship(int _x, int _y, int _health, int _status, Weapon _weapon, Sprite _image, int screen_width, int screen_height) :
                                                                                                              x(_x),
                                                                                                              y(_y),
                                                                                                              health(_health),
                                                                                                              status(_status),
                                                                                                              weapon(_weapon),
                                                                                                              image(_image) {
    // LOGI("Constructeur");

    this->length_x = 0;
    this->length_y = 0;
    this->destination_x = 0;
    this->destination_y = 0;
    // TODO Passer les valeurs de l'attribut screen de l'objet Window
    this->area_limits = { 0, 0, screen_width, screen_height };

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
    status = _ship.status;
    weapon = _ship.weapon;
    image = _ship.image;
    area_limits = _ship.area_limits;
    fired_weapons = _ship.fired_weapons;
}

Ship::~Ship() {

}

int Ship::get_x() {
    return this->x;
}

int Ship::get_y() {
    return this->y;
}

void Ship::set_sprite(Sprite _image) {
    this->image = _image;
}

Sprite Ship::get_sprite() {
    return this->image;
}

void Ship::dec_status(int _status) {
    this->status -= _status;
}
void Ship::set_status(int _status) {
    this->status = _status;
}

int Ship::get_status() {
    return this->status;
}

void Ship::set_health(int _health) {
    this->health = _health;
}

int Ship::get_health() {
    return this->health;
}

bool Ship::alive() {
    return this->get_health() > 0;
}

bool Ship::in_area_limit() {
    if (this->get_x() >= this->area_limits.x && this->get_x() <= this->area_limits.w &&
        this->get_y() >= this->area_limits.y && this->get_y() <= this->area_limits.h) {
        return true;
    }

    return false;
}

void Ship::render(SDL_Renderer *_renderer) {
    this->image.render(this->x, this->y, _renderer);

    // WTF cette méthode ? Les weapons sont déjà render dans LevelX
    for (Weapon *fired_weapon : this->fired_weapons) {
        // if (fired_weapon.get_fired() == true) {
        // if (this->weapon.x != this->x || this->weapon.y != this->y) {
            fired_weapon->render(_renderer);
        // }
    }
}
