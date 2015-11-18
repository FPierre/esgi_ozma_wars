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

OwnShip::OwnShip(int _x, int _y, int _health, int _status, Weapon _weapon, Sprite *_image, Sprite *_image_left, Sprite *_image_right, int screen_width, int screen_height) :
    Ship(_x, _y, _health, _status, _weapon, _image, screen_width, screen_height) {

    // LOGI("Constructeur");
    this->image_front = _image;
    this->image_left = _image_left;
    this->image_right = _image_right;
    this->fired_weapon_limit = 100;

    this->destroy_sound = Mix_LoadWAV("sounds/explosion.wav");

    if (this->destroy_sound == NULL) {
        LOGI("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

OwnShip::OwnShip(const OwnShip& _ship) {
    // LOGI("Constructeur par copie");

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
}

OwnShip::~OwnShip() {

}

void OwnShip::move() {
    float accelerometer_values[3];
    Android_JNI_GetAccelerometerValues(accelerometer_values);

    float tmp_x_value = this->x + (21 * accelerometer_values[0]);
    float tmp_y_value = this->y + (21 * accelerometer_values[1]);

    // TODO Passer cette partie dans constructeur (ce calcul n'est pas a faire ici)
    int ship_width = this->image->get_width() * 2;
    int ship_height = this->image->get_height() * 2;

    // TODO Buggé, à finir (va dans le else, mais ne set pas le sprite image)
    if (this->x > tmp_x_value + 2) {
        set_sprite(this->image_right);
    }
    else if (this->x < tmp_x_value - 2) {
        set_sprite(this->image_left);
    }
    else {
        set_sprite(this->image_front);
    }

    if (tmp_x_value >= this->area_limits.x && tmp_x_value <= (this->area_limits.w - ship_width)) {
        this->x = tmp_x_value;
    }

    if (tmp_y_value >= this->area_limits.y && tmp_y_value <= (this->area_limits.h - ship_height)) {
        this->y = tmp_y_value;
    }
}

/**
 * Tire des missiles vers le haut de l'écran uniquement
 */
bool OwnShip::fire() {
    // Si le vaisseau n'a pas encore atteint le nombre limte de missiles qu'il peut tirer simultanément
    if (this->fired_weapons.size() < this->fired_weapon_limit) {
        // Copie de Weapon actuelle du vaisseau
        Weapon *fired_weapon = &(this->weapon);

        fired_weapon->set_x(this->x);
        fired_weapon->set_y(this->y);
        fired_weapon->set_destination(this->x, 0);

        // Si dans ce vector, c'est que missile a été tiré. Pas besoin de faire de vérifs.
        this->fired_weapons.push_back(fired_weapon);

        return true;
    }

    return false;
}
