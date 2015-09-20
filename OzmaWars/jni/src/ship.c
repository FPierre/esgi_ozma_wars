#include "ship.h"
#include "SDL.h"

Ship *ship_init(int x, int y, int size, int max_health, Weapon weapon) {
    Ship *ship = malloc(sizeof(Ship));
    ship->x = x;
    ship->y = y;
    ship->size = size;
    ship->health = ship->max_health = max_health;
    ship->rectangle.x = ship->x;
    ship->rectangle.y = ship->y;
    ship->rectangle.w = ship->size;
    ship->rectangle.h = ship->size;
    ship->weapon = weapon;

    return ship;
}

void ship_fire() {

}
