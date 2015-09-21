#ifndef WEAPON_H
#define WEAPON_H

#include "sprite.h"

#define PI 3.14159265

// typedef struct {
//     // int type;
//     // struct Object ?
//     int x;
//     int y;
//     Ship ship;
// } Target;

typedef struct {
    int x;
    int y;
    int w;
    int h;
    double angle;
    int strength;
    int speed;
    Sprite *image;
    SDL_Rect body;
} Weapon;

Weapon *weapon_init(int w, int h, double angle, int strength, int speed, Sprite *image);
void weapon_render(SDL_Renderer *renderer, Weapon *weapon);

#endif
