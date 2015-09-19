#include "ship.h"
#include "SDL.h"

Ship *init_ship(int x, int y, int size, int max_health) {
    Ship *ship = malloc(sizeof(Ship));
    ship->x = x;
    ship->y = y;
    ship->size = size;
    ship->health = ship->max_health = max_health;
    ship->rectangle.x = ship->x;
    ship->rectangle.y = ship->y;
    ship->rectangle.w = ship->size;
    ship->rectangle.h = ship->size;

    return ship;
}
