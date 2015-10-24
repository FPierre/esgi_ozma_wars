#include <android/log.h>

#include "headers/EnemyShip.h"

const double PI = 3.14159265358979323846;

#define LOG_TAG "EnemyShip"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

EnemyShip::EnemyShip() : Ship() {

}

EnemyShip::EnemyShip(int _x, int _y, int _health, Weapon _weapon, Sprite *_image) : Ship(_x, _y, _health, _weapon, _image) {
    // LOGI("Constructeur");
}

// EnemyShip::EnemyShip(const EnemyShip& _ship) {
//     LOGI("Constructeur par copie");
//
//     x = _ship.x;
//     y = _ship.y;
//     health = _ship.health;
//     weapon = _ship.weapon;
//     image = _ship.image;
// }

// EnemyShip::~EnemyShip() {
//
// }

void EnemyShip::set_destination(int _x, int _y) {
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

    this->sprite->set_angle(angle);
}

void EnemyShip::move() {
    // LOGI("this->x : %d", this->x);
    // LOGI("this->y : %d", this->y);
    // LOGI("this->destination_x : %d", this->destination_x);
    // LOGI("this->destination_y : %d", this->destination_y);

    // TODO Gérer la vitesse par / 100
    if (this->x < this->destination_x) {
        this->x += this->length_x / 200;
    }

    if (this->y < this->destination_y) {
        this->y += this->length_y / 200;
    }
}
