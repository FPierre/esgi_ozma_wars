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

    int w = this->window.get_width();

    Weapon canon(100, &(this->game.missile_image));

    OwnShip own_ship(0, 0, 100, canon, &(this->game.own_ship_image),
                                       &(this->game.own_ship_image_left),
                                       &(this->game.own_ship_image_right));
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
        if (event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN) {
            this->game.own_ship.fire();
            // TODO Mieux encapsuler cette méthode
            Mix_PlayChannel(-1, this->game.own_ship.weapon.launch_sound, 0);
        }
    }
}

void LevelOne::logic() {
    this->game.own_ship.move();

    // Pour tous les missiles tirés de notre vaiseau
    for (Weapon *fired_weapon : this->game.own_ship.fired_weapons) {
        fired_weapon->move();
    }

    this->enemy_ships[0].move();
    this->enemy_ships[0].weapon.move();

    // Niveau suivant
    // Pas encore effectif
    if (this->game.get_score() > 5) {
        // set_next_state(STATE_LEVEL_TWO);
    }

    // Sortie de jeu
    // Pas encore effectif
    if (this->game.own_ship.alive() == false) {
        // set_next_state(STATE_EXIT);
    }
}

void LevelOne::render() {
    SDL_RenderClear(this->window.renderer);

    this->game.render_score();
    this->game.render_life();

    for (EnemyShip enemy_ship : this->enemy_ships) {
        enemy_ship.render(this->window.renderer);
    }

    this->game.own_ship.render(this->window.renderer);

    // SDL_SetRenderDrawColor(this->window.renderer, 226, 35, 35, SDL_ALPHA_OPAQUE);
    // SDL_SetRenderDrawColor(this->window.renderer, 35, 226, 35, SDL_ALPHA_OPAQUE);
    SDL_SetRenderDrawColor(this->window.renderer, 35, 35, 226, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(this->window.renderer);

    SDL_Delay(10);
}
