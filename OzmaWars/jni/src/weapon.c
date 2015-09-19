#include "weapon.h"

Weapon *weapon_init(int strength) {
    Weapon *weapon = malloc(sizeof(Weapon));
    weapon->strength = strength;

    return weapon;
}
