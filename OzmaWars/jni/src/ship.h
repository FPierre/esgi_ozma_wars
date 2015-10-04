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
    int mov_to_target_x;
    int mov_to_target_y;
    int health;
    int max_health;
    Weapon *weapon;
    Sprite *image;
    Target target;
    SDL_Rect body;
} Ship;

Ship *ship_init(int x, int y, int w, int h, double angle, int max_health, Sprite *image, Weapon *weapon);
void ship_render(SDL_Renderer *renderer, Ship *ship);
void ship_fire(Ship *ship, Ship *target);
void ship_set_ride(Ship *ship, int x, int y);
int ship_move(Ship *ship);
int checkCollision(Ship *ship, Ship *enemy_ship, int mode);
void ship_destroyed(Ship *ship, Sprite *image, int state);

#endif
