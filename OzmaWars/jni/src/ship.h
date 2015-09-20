#ifndef SHIP_H
#define SHIP_H

#include "weapon.h"
#include "SDL.h"

typedef struct {
    int x;
    int y;
    int size;
    int health;
    int max_health;
    Weapon weapon;
    SDL_Rect rectangle;
} Ship;

Ship *ship_init(int x, int y, int size, int max_health, Weapon weapon);
void ship_fire();

#endif
