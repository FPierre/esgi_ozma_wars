#ifndef SHIP_H
#define SHIP_H

#include "weapon.h"
#include "SDL.h"

#define LEFT_SENSIBILITY = -5
#define RIGHT_SENSIBILITY = 5

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
