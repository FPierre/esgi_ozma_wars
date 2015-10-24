#include <android/log.h>
#include "SDL.h"

#include "headers/LevelOne.h"
#include "headers/Game.h"

#define LOG_TAG "LevelOne"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

LevelOne::LevelOne(Game _game, Window _window) : game(_game),
                                                 window(_window) {

    // LOGI("Constructeur");

    // Rgb blue_background(0, 255, 255);
    // Sprite missile_image(55, 390, 50, 20, 0.0, "spritesheets/projectile.bmp", blue_background, this->window.renderer);
    // this->sprites["missile"] = missile_image;

    // Rgb pink_background(255, 0, 255);
    // Sprite ship_image(155, 303, 30, 28, 180, "spritesheets/ship.bmp", pink_background, this->window.renderer);
    // this->sprites["ship"] = ship_image;

    // Sprite m = this->game.missile_image;

    // if (&m != nullptr) {
    //     Weapon canon(100, &m);

    //     Sprite s = this->game.ship_image;

    //     if (&s != nullptr) {
    //         Ship ship1(0, 0, 100, canon, &s);

    //         if (&ship1 != nullptr) {
    //             LOGI("Ship ship1 a pu être crée");
    //             this->sh = ship1;
    //         }
    //         else {
    //             LOGI("Ship ship1 n'a pas pu être crée");
    //         }
    //     }
    //     else {
    //         LOGI("Sprite s n'a pas pu être crée");
    //     }
    // }
    // else {
    //     LOGI("Sprite m n'a pas pu être crée");
    // }



    int w = this->window.get_width();

    Weapon canon(100, &(this->game.missile_image));

    OwnShip own_ship(0, 0, 100, canon, &(this->game.own_ship_image));
    this->game.own_ship = own_ship;

    EnemyShip enemy_ship_1(0, 0, 100, canon, &(this->game.enemy_ship_image));
    enemy_ship_1.set_destination(w, 0);
    enemy_ship_1.fire(1000, 800);
    this->enemy_ships.push_back(enemy_ship_1);

    // EnemyShip enemy_ship_2(50, 0, 100, canon, &(this->game.enemy_ship_image));
    // this->enemy_ships.push_back(enemy_ship_2);

    // EnemyShip enemy_ship_3(100, 0, 100, canon, &(this->game.enemy_ship_image));
    // this->enemy_ships.push_back(enemy_ship_3);
}

LevelOne::LevelOne(const LevelOne& _level_one) {
    // LOGI("Constructeur par copie");

    game = _level_one.game;
    window = _level_one.window;
    enemy_ships = _level_one.enemy_ships;
}

LevelOne::~LevelOne() {

}

void LevelOne::handle_events() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        // myDot.handle_input();

        if (event.type == SDL_QUIT) {
            // set_next_state(STATE_EXIT);
        }
    }
}

void LevelOne::logic() {
    // Vérification des collisions
    for (EnemyShip enemy_ship : this->enemy_ships) {
        // Si un missile du Own Ship touche un Enemy Ship
        if ( this->game.check_collision(this->game.own_ship.weapon, enemy_ship) ) {
            LOGI("N°: "+i+" = COLLISION FOUND");
        } else {
            LOGI("N°: "+i+" = NOT COLLISION");
        }

        // Si un missile des Enemy Ships touche le Own Ship
        if ( this->game.check_collision(this->game.own_ship, enemy_ship.weapon) ) {
            LOGI("N°: "+i+" = COLLISION FOUND");
        } else {
            LOGI("N°: "+i+" = NOT COLLISION");
        }
    }

    // Mouvements des objets
    this->game.own_ship.move();

    this->enemy_ships[0].move();
    this->enemy_ships[0].weapon.move();

    // this->enemy_ships[0].move(w, 0);
    // // // this->enemy_ships[0].fire(300, 400);

    // this->enemy_ships[1].move(550, 0);
    // // // this->enemy_ships[1].fire(700, 200);

    // this->enemy_ships[2].move(600, 0);

    // If the dot went to the exit
    // if (check_collision(myDot, exit) == true) {
    //     // Go to the overworld
    //     set_next_state(STATE_GREEN_OVERWORLD);
    // }

    // // Move the dot
    // myDot.move();
}

void LevelOne::render() {
    SDL_RenderClear(this->window.renderer);

// TTF_Init();
// TTF_Font *font = TTF_OpenFont("fonts/consola.ttf", 30);
// SDL_Color text_color = { 0, 0, 0 };
// SDL_Surface *message = TTF_RenderText_Solid(font, "test", text_color);
// SDL_Texture* texture = SDL_CreateTextureFromSurface(this->window.renderer, message);
// int mWidth = message->w;
// int mHeight = message->h;
// SDL_Rect test = { 10, 10, mWidth, mHeight };

// SDL_RenderCopy(this->window.renderer, texture, NULL, &test);

// this->game.render_score();


    for (EnemyShip enemy_ship : this->enemy_ships) {
        enemy_ship.render(this->window.renderer);
    }

    this->game.own_ship.render(this->window.renderer);

    // SDL_SetRenderDrawColor(this->window.renderer, 226, 35, 35, SDL_ALPHA_OPAQUE);
    SDL_SetRenderDrawColor(this->window.renderer, 35, 226, 35, SDL_ALPHA_OPAQUE);
    // SDL_SetRenderDrawColor(this->window.renderer, 35, 35, 226, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(this->window.renderer);

    SDL_Delay(10);
}
