// #include <cmath>
#include "weapon.h"

Weapon *weapon_init(int strength) {
    Weapon *weapon = malloc(sizeof(Weapon));
    weapon->strength = strength;
    weapon->speed = 1;

    return weapon;
}

// void fire(Weapon *weapon, Target *target, SDL_Renderer *renderer) {

// }
