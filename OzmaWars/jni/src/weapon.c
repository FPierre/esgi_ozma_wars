#include "weapon.h"

Weapon *weapon_init(int w, int h, double angle, int strength, int speed, Sprite *image) {
    Weapon *weapon = malloc(sizeof(Weapon));
    weapon->x = 100;
    weapon->y = 100;
    weapon->w = w;
    weapon->h = h;
    weapon->angle = angle;
    weapon->mov_to_target_x = 0;
    weapon->mov_to_target_y = 0;
    weapon->strength = strength;
    weapon->speed = speed;
    weapon->body.x = weapon->x;
    weapon->body.y = weapon->y;
    weapon->body.w = weapon->w;
    weapon->body.h = weapon->h;
    weapon->image = image;

    return weapon;
}

void weapon_render(SDL_Renderer *renderer, Weapon *weapon) {
    SDL_RenderCopyEx(renderer, weapon->image->texture, &(weapon->image->image_location), &(weapon->body), weapon->angle, NULL, SDL_FLIP_NONE);
}
