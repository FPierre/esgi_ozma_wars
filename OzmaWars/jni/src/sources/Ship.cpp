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

    this->weapon.x = _x;
    this->weapon.y = _y;
    this->length_x = 0;
    this->length_y = 0;
    this->destination_x = 0;
    this->destination_y = 0;
    // TODO Passer les valeurs de l'attribut screen de l'objet Window
    this->area_limits = { 0, 0, 1920, 1080 };
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
}

Ship::~Ship() {

}

int Ship::get_x() { return this->x; }
int Ship::get_y() { return this->y; }
Sprite *Ship::get_sprite() { return this->sprite; }

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
    if (this->alive()) {
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

void Ship::fire(int _x, int _y) {
    this->weapon.set_destination(_x, _y);
}
