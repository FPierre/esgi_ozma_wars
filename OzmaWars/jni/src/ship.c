#include "math.h"
#include "ship.h"

#define PI 3.14159265

Ship *ship_init(int x, int y, int w, int h, double angle, int max_health, Sprite *image, Weapon *weapon) {
    Ship *ship = malloc(sizeof(Ship));
    ship->x = x; // Utile ? Plutot passer par body ?
    ship->y = y; // Utile ? Plutot passer par body ?
    ship->w = w;
    ship->h = h;
    ship->angle = angle;
    ship->mov_to_target_x = 0;
    ship->mov_to_target_y = 0;
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

void ship_fire(Ship *ship, Ship *target) {
    double val = 180.0 / PI;
    int start_x = ship->x;
    int start_y = ship->y;
    int end_x = target->x;
    int end_y = target->y;
    int diff_x = end_x - start_x;
    int diff_y = end_y - start_y;
    int length = sqrt(diff_x * diff_x + diff_y * diff_y);
    double angle = atan2(diff_y, diff_x) * val;

    ship->weapon->angle = angle;
    ship->weapon->mov_to_target_x = diff_x;
    ship->weapon->mov_to_target_y = diff_y;
}

void ship_set_ride(Ship *ship, int x, int y) {
    double val = 180.0 / PI;
    int start_x = ship->x;
    int start_y = ship->y;
    int end_x = x;
    int end_y = y;
    int diff_x = end_x - start_x;
    int diff_y = end_y - start_y;
    int length = sqrt(diff_x * diff_x + diff_y * diff_y);
    double angle = atan2(diff_y, diff_x) * val;

    ship->angle = angle;
    ship->mov_to_target_x = diff_x;
    ship->mov_to_target_y = diff_y;
    ship->target.x = end_x;
    ship->target.y = end_y;
}

int ship_move(Ship *ship) {
    if (ship->body.x < ship->target.x) {
        ship->body.x += ship->mov_to_target_x / 100;
    }

    if (ship->body.y < ship->target.y) {
        ship->body.y += ship->mov_to_target_y / 100;
    }

    if (ship->body.x >= ship->target.x && ship->body.y >= ship->target.y) {
        return 1;
    }
    else {
        return 0;
    }
}

int checkCollision(Ship *ship, Ship *enemy_ship) {
    // Initialisation des variables (A = Ship, B = Enemy Ship, C = Weapon's Enemy Ship)
    int leftA,   leftB,   leftC;
    int rightA,  rightB,  rightC;
    int topA,    topB,    topC;
    int bottomA, bottomB, bottomC;

    // Calcule les côtés du Ship (A)
    leftA =     ship->body.x;
    rightA =    ship->body.x + ship->w;
    topA =      ship->body.y;
    bottomA =   ship->body.y + ship->h;

    // Calcule les côtés du Enemy Ship (B)
    leftB =     enemy_ship->body.x;
    rightB =    enemy_ship->body.x + enemy_ship->w;
    topB =      enemy_ship->body.y;
    bottomB =   enemy_ship->body.y + enemy_ship->h;

    // Calcule les côtés du Weapon (C)
    Weapon *weapon = enemy_ship->weapon;
    leftC =     weapon->body.x;
    rightC =    weapon->body.x + weapon->w;
    topC =      weapon->body.y;
    bottomC =   weapon->body.y + weapon->h;

    // Si un seul des côtés de B ou de C est hors zone de A, alors il n'y a pas de collision possible
    if( bottomB <= topA && bottomC <= topA ) { return 0; }
    if( topB >= bottomA && topC >= bottomA ) { return 0; }
    if( rightB <= leftA && rightC <= leftA ) { return 0; }
    if( leftB >= rightA && leftC >= rightA ) { return 0; }

    // Si aucun des côtés de B ou de C est hors zone de A, alors il y a collision
    return 1;
}


void ship_destroyed(Ship *ship, Sprite *image, int state) {
    switch (state) {
        case 0:
            ship->image = image;
            break;
        case 7:
            sprite_position(image, 78, 132, 90, 90);
            break;
        case 14:
            sprite_position(image, 168, 132, 103, 90);
            break;
        case 21:
            sprite_position(image, 0, 0, 0, 0);
            break;
        case 28: // détruire Ship -> Game Over!
            break;
    }
}
