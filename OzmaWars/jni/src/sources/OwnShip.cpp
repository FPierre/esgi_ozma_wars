#include <android/log.h>
#include "android/sensor.h"
#include "../sdl/src/core/android/SDL_android.h"

#include "headers/OwnShip.h"

const double PI = 3.14159265358979323846;

#define LOG_TAG "OwnShip"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

OwnShip::OwnShip() : Ship() {

}

OwnShip::OwnShip(int _x, int _y, int _health, int _status, Weapon _weapon, Sprite _image, Sprite _image_left, Sprite _image_right, int screen_width, int screen_height) :
    Ship(_x, _y, _health, _status, _weapon, _image, screen_width, screen_height) {

    this->image_front = _image;
    this->image_left = _image_left;
    this->image_right = _image_right;
    this->fired_weapon_limit = 100;

    this->ship_width = this->image.get_width() * 2;
    this->ship_height = this->image.get_height() * 2;

    this->destroy_sound = Mix_LoadWAV("sounds/explosion.wav");

    if (this->destroy_sound == NULL) {
        LOGI("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

OwnShip::OwnShip(const OwnShip& _ship) {
    x = _ship.x;
    y = _ship.y;
    health = _ship.health;
    status = _ship.status;
    weapon = _ship.weapon;
    image = _ship.image;
    image_front = _ship.image_front;
    image_left = _ship.image_left;
    image_right = _ship.image_right;
    fired_weapon_limit = _ship.fired_weapon_limit;
    destroy_sound = _ship.destroy_sound;
    ship_width = _ship.ship_width;
    ship_height = _ship.ship_height;
}

OwnShip::~OwnShip() {

}

// Mouvement du vaisseau
void OwnShip::move() {
    float accelerometer_values[3];
    Android_JNI_GetAccelerometerValues(accelerometer_values);

    float tmp_x_value = this->x + (21 * accelerometer_values[0]);
    float tmp_y_value = this->y + (21 * accelerometer_values[1]);

    if (this->x > tmp_x_value + 5) {
        set_sprite(this->image_right);
    }
    else if (this->x < tmp_x_value - 5) {
        set_sprite(this->image_left);
    }
    else {
        set_sprite(this->image_front);
    }

    if (tmp_x_value >= this->area_limits.x && tmp_x_value <= (this->area_limits.w - this->ship_width)) {
        this->x = tmp_x_value;
    }

    if (tmp_y_value >= this->area_limits.y && tmp_y_value <= (this->area_limits.h - this->ship_height)) {
        this->y = tmp_y_value;
    }
}

// Tire des missiles vers le haut de l'écran uniquement
void OwnShip::fire() {
    // Si le vaisseau n'a pas encore atteint le nombre limite de missiles qu'il peut tirer simultanément
    if (this->fired_weapons.size() < this->fired_weapon_limit) {
        // Copie de Weapon actuelle du vaisseau
        Weapon *fired_weapon = new Weapon(100, this->weapon.get_sprite(), this->area_limits.w, this->area_limits.h);

        fired_weapon->set_x(this->x);
        fired_weapon->set_y(this->y);
        fired_weapon->set_destination(this->x, 0, true);

        Mix_PlayChannel(-1, fired_weapon->launch_sound, 0);

        this->fired_weapons.push_back(fired_weapon);
    }
}
