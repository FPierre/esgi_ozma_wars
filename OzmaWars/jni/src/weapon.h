#ifndef WEAPON_H
#define WEAPON_H

#include "SDL.h"

typedef struct {
    int strength;
} Weapon;

Weapon *weapon_init(int strength);

#endif
