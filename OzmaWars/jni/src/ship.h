#ifndef SHIP_H
#define SHIP_H

#include "SDL.h"
#include "weapon.h"

typedef struct {
    int x;
    int y;
    int w;
    int h;
    double angle;
    int health;
    int max_health;
    Weapon *weapon;
    Sprite *image;
    SDL_Rect body;
} Ship;

Ship *ship_init(int x, int y, int w, int h, double angle, int max_health, Sprite *image, Weapon *weapon);
void ship_render(SDL_Renderer *renderer, Ship *ship);
void ship_fire(Ship *ship, Ship *target);

#endif
