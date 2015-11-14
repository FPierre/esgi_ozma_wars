#include <android/log.h>
#include <math.h>

#include "headers/Weapon.h"

const double PI = 3.14159265358979323846;

#define LOG_TAG "Weapon"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

Weapon::Weapon() {

}

Weapon::Weapon(int _strength, Sprite *_image) : strength(_strength),
                                                image(_image) {
    // this->x = 0;
    // this->y = 0;
    this->fired = false;
    this->length_x = 0;
    this->length_y = 0;
    this->destination_x = 0;
    this->destination_y = 0;

    // TODO Passer les valeurs de l'attribut screen de l'objet Window
    this->area_limits = { 0, 0, 1920, 1080 };

    this->launch_sound = Mix_LoadWAV("sounds/missile_launch.wav");

    if (this->launch_sound == NULL) {
        LOGI("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

Weapon::Weapon(const Weapon& _weapon) {
    x = _weapon.x;
    y = _weapon.y;
    fired = _weapon.fired;
    length_x = _weapon.length_x;
    length_y = _weapon.length_y;
    destination_x = _weapon.destination_x;
    destination_y = _weapon.destination_y;
    strength = _weapon.strength;
    image = _weapon.image;
    launch_sound = _weapon.launch_sound;
}

Weapon::~Weapon() {

}

void Weapon::render(SDL_Renderer *_renderer) {
    this->image->render(this->x, this->y, _renderer);
}

void Weapon::set_fired(bool _fired) {
    this->fired = _fired;
}

bool Weapon::get_fired() {
    return this->fired;
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

int Weapon::get_x() { return this->x; }
int Weapon::get_y() { return this->y; }
Sprite *Weapon::get_sprite() { return this->image; }

void Weapon::move() {
    // LOGI("this->x : %d", this->x);
    // LOGI("this->y : %d", this->y);
    // LOGI("this->destination_x : %d", this->destination_x);
    // LOGI("this->destination_y : %d", this->destination_y);


    // Le missile ne doit pas s'arreter s'il atteint sa "destination"
    // S'il ne touche pas un vaisseau, il sort de l'écran
    // TODO Gérer la vitesse par / 50
    // if (this->x < this->destination_x) {
        this->x += this->length_x / 80;
    // }

    // if (this->y < this->destination_y) {
        this->y += this->length_y / 80;
    // }
}
