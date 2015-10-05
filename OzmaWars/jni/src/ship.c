#include "math.h"
#include "ship.h"
#include <android/log.h>

#define PI 3.14159265
#define  LOG_TAG    "SHIP NATIVE"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

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

int checkCollision(Ship *ship, Ship *enemy_ships[], int length_enemy_ships) {
    // Initialisation des variables (A = Ship, B = Enemy Ship)
    int leftA,   leftB;
    int rightA,  rightB;
    int topA,    topB;
    int bottomA, bottomB;

    // Calcule les côtés du Ship (A)
    leftA =     ship->body.x;
    rightA =    ship->body.x + ship->w;
    topA =      ship->body.y;
    bottomA =   ship->body.y + ship->h;

    // Détermine les collisions d'après les Enemy Ships présents dans le tableau
    int     i=0, 
            weapons_length=0,
            do_collision=0;
    Weapon  *weapons[ length_enemy_ships ];

    LOGI("START - do_collision = %d", do_collision);
    LOGI("REAL ARRAY SIZE = %d", length_enemy_ships);

    for (i=0; i < length_enemy_ships; ++i) {
        LOGI("SHIPS : loop - ship (%d)", i);
        // Calcule les côtés du Enemy Ship (B)
        leftB =     enemy_ships[i]->body.x;
        rightB =    enemy_ships[i]->body.x + enemy_ships[i]->w;
        topB =      enemy_ships[i]->body.y;
        bottomB =   enemy_ships[i]->body.y + enemy_ships[i]->h;

        if (enemy_ships[i]->weapon != NULL) {
            LOGI("SHIPS : loop - Ajout du weapon dans le tableau");
            weapons[i] = enemy_ships[i]->weapon;
            ++weapons_length;
        }

        LOGI("SHIPS : loop - ship (%d) TESTS", i);

        // Si un seul des côtés de B est hors zone de A, alors il n'y a pas de collision possible
        if( bottomB <= topA ) { LOGI("A"); continue; }
        if( topB >= bottomA ) { LOGI("B"); continue; }
        if( rightB <= leftA ) { LOGI("C"); continue; }
        if( leftB >= rightA ) { LOGI("D"); continue; }

        LOGI("SHIPS : loop - ship (%d) COLLISION FOUND", i);

        // Si aucun des côtés de B ou de C est hors zone de A, alors il y a collision
        do_collision=1;
        LOGI("SHIPS : loop ends - do_collision = %d", do_collision);
    }

    LOGI("SHIPS : loop ends - do_collision = %d", do_collision);

    if (do_collision != 1 && weapons_length != 0 && weapons != NULL) {
        for (i=0; i < weapons_length; ++i) {
            LOGI("WEAPONS : loop - weapon (%d)", i);
            // Calcule les côtés du Weapon (C = Weapon's Enemy Ship)
            Weapon *weapon = weapons[i];

            int leftC =     weapon->body.x;
            int rightC =    weapon->body.x + weapon->w;
            int topC =      weapon->body.y;
            int bottomC =   weapon->body.y + weapon->h;

            LOGI("WEAPONS : loop - weapon (%d) TESTS WEAPON", i);

            if( bottomC <= topA ) { LOGI("A_1"); continue; }
            if( topC >= bottomA ) { LOGI("B_1"); continue; }
            if( rightC <= leftA ) { LOGI("C_1"); continue; }
            if( leftC >= rightA ) { LOGI("D_1"); continue; }

            LOGI("WEAPONS : loop - weapon (%d) COLLISION FOUND WITH WEAPON", i);

            // Si aucun des côtés de B ou de C est hors zone de A, alors il y a collision
            do_collision=1;
        }
    }

    LOGI("END - return do_collision = %d", do_collision);
    // On renvoit le résultat des tests
    return do_collision;
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
        case 22: // détruire Ship -> Game Over!
            ship = NULL;
            break;
    }
}
