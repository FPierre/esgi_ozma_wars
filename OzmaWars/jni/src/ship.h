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
    Weapon weapons;
    SDL_Rect rectangle;
} Ship;

Ship *init_ship(int x, int y, int size, int max_health);

#endif
