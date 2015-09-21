#include "ship.h"

Ship *ship_init(int x, int y, int w, int h, double angle, int max_health, Sprite *image, Weapon *weapon) {
    Ship *ship = malloc(sizeof(Ship));
    ship->x = x; // Utile ? Plutot passer par body ?
    ship->y = y; // Utile ? Plutot passer par body ?
    ship->w = w;
    ship->h = h;
    ship->angle = angle;
    ship->health = ship->max_health = max_health;
    ship->body.x = ship->x;
    ship->body.y = ship->y;
    ship->body.w = ship->w;
    ship->body.h = ship->h;
    ship->image = image;
    ship->weapon = weapon;

    return ship;
}

void ship_render(SDL_Renderer *renderer, Ship *ship) {
    SDL_RenderCopyEx(renderer, ship->image->texture, &(ship->image->image_location), &(ship->body), ship->angle, NULL, SDL_FLIP_NONE);
}
