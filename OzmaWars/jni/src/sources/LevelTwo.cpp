#include <android/log.h>
#include "SDL.h"

#include "headers/LevelTwo.h"
#include "headers/Game.h"
#include "headers/Sprite.h"

#define LOG_TAG "LevelTwo"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

const int STATUS_NORMAL      = 80;
const int STATUS_DESTROY_END = 0;

LevelTwo::LevelTwo(Game *_game) : game(_game) {
    LOGI("LevelTwo");

    this->background = SDL_LoadBMP("images/background_level_two.bmp");

    if (this->background == NULL) {
        LOGI("Sprite non trouve");
        LOGI("%s\n", SDL_GetError());
        exit(0);
    }

    this->texture = SDL_CreateTextureFromSurface(this->game->get_window().renderer, this->background);
    this->image_location = { 0, 0, 1920, 1080 };
    this->test = { 0, 0, 1920, 1080};

    int screen_width = this->game->get_window().get_width();
    int screen_height = this->game->get_window().get_height();

    Weapon canon(100, this->game->missile_image, screen_width, screen_height);

    EnemyShip enemy_ship_1(0, 0, 100, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_1);
}

LevelTwo::LevelTwo(const LevelTwo& _level_two) {
    // LOGI("Constructeur par copie");

    game = _level_two.game;
    enemy_ships = _level_two.enemy_ships;
    background = _level_two.background;
    texture = _level_two.texture;
    image_location = _level_two.image_location;
    test = _level_two.test;
}

LevelTwo::~LevelTwo() {
}

void LevelTwo::handle_events() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        // Si "tap" sur l'écran, Own ship tire
        if (event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN) {
            this->game->own_ship.fire();
        }
    }
}

void LevelTwo::logic() {
    // TESTS déplacement random

    for (EnemyShip& enemy_ship : this->enemy_ships) {
        // Déplacement sur x doit être plus important que déplacement sur y
        int random_number_for_x = rand() % 5 + 1;
        uint min = -10;
        uint max = 1;
        int random_number_for_y = min + (rand() % (int)(max - min + 1));

        // LOGI("random_number_for_y : %d", random_number_for_y);

        int test1 = random_number_for_x + enemy_ship.get_x();
        int test2 = random_number_for_y + enemy_ship.get_y();

        // LOGI("test2 : %d", test2);

        enemy_ship.set_destination(test1, test2);
        enemy_ship.move();
    }
}

void LevelTwo::render() {
   SDL_RenderClear(this->game->get_window().renderer);

    // Image de background
    SDL_RenderCopy(this->game->get_window().renderer, this->texture, NULL, NULL);

    this->game->render_score();
    this->game->render_life();

    for (EnemyShip& enemy_ship : this->enemy_ships) {
        // LOGI("Health of enemy ship: %d", enemy_ship.get_health());
        if ( !enemy_ship.alive() ) {
            // LOGI("Enemy ship - not alive");
            // Méthode d'affichage de la destruction
            this->game->render_destroy(enemy_ship);
        }
        // LOGI("Enemy ship - render");
        // Render du Sprite
        enemy_ship.render(this->game->get_window().renderer);
    }

    // On vérifie que le Ship n'a toujours pas explosé
    if ( this->game->own_ship.get_status() != STATUS_DESTROY_END ) {
        // S'il n'est plus en vie, on gère l'animation de l'explosion
        if ( !this->game->own_ship.alive() ) {
            // Méthode d'affichage de la destruction
            this->game->render_destroy(this->game->own_ship);
        }
        // Render du Sprite
        this->game->own_ship.render(this->game->get_window().renderer);
    } else {
        // On affiche l'écran GameOver
        this->game->render_over();
    }


    // SDL_SetRenderDrawColor(this->game->get_window().renderer, 226, 35, 35, SDL_ALPHA_OPAQUE);
    // SDL_SetRenderDrawColor(this->game->get_window().renderer, 35, 226, 35, SDL_ALPHA_OPAQUE);
    // SDL_SetRenderDrawColor(this->game->get_window().renderer, 35, 35, 226, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(this->game->get_window().renderer);

    SDL_Delay(10);
}
