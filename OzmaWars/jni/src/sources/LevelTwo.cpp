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
    this->background = SDL_LoadBMP("images/background_level_two.bmp");

    if (this->background == NULL) {
        LOGI("Sprite non trouve");
        LOGI("%s\n", SDL_GetError());
        exit(0);
    }

    this->texture = SDL_CreateTextureFromSurface(this->game->get_window().renderer, this->background);
    this->image_location = { 0, 0, this->game->get_window().get_width(), this->game->get_window().get_height() };
    this->test = { 0, 0, this->game->get_window().get_width(), this->game->get_window().get_height() };

    int screen_width = this->game->get_window().get_width();
    int screen_height = this->game->get_window().get_height();

    Weapon canon(40, this->game->missile_image, screen_width, screen_height);
    canon.set_speed(14);

    EnemyShip enemy_ship_1(0, 0, 150, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_1);

    EnemyShip enemy_ship_2(-50, 200, 150, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_2);

    EnemyShip enemy_ship_3(-600, 80, 150, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_3);

    EnemyShip enemy_ship_4(-840, 370, 150, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_4);

    // S'il n'y a pas encore de musique jouée
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(this->game->music, -1);
    }
}

LevelTwo::LevelTwo(const LevelTwo& _level_two) {
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
        if (this->game->own_ship.alive() && event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN) {
            this->game->own_ship.fire();
        } else if (event.type == SDL_KEYDOWN) {
            exit(0);
        }
    }
}

void LevelTwo::logic() {
    // Variations random des déplacements des ennemis
    for (EnemyShip& enemy_ship : this->enemy_ships) {
        // Déplacement sur x doit être plus important que déplacement sur y
        int random_number_for_x = rand() % 5 + 1;
        uint min = -10;
        uint max = 1;
        int random_number_for_y = min + (rand() % (int)(max - min + 1));

        int test1 = random_number_for_x + enemy_ship.get_x();
        int test2 = random_number_for_y + enemy_ship.get_y();

        enemy_ship.set_destination(test1, test2);
    }

    // Vérification des status des vaisseaux et des collisions

    int size = this->enemy_ships.size();

    for (int i = 0; i < size; ++i) {
        EnemyShip& enemy_ship = this->enemy_ships[i];

        // Si le vaisseau ennemi est détruit
        if (!enemy_ship.alive() && enemy_ship.get_status() == STATUS_DESTROY_END) {
            enemy_ship.set_health(0);

            continue;
        }
        else if (enemy_ship.alive() && enemy_ship.get_status() == STATUS_NORMAL) {
            enemy_ship.move();
            // Vise Own ship
            enemy_ship.fire(this->game->own_ship.get_x(), this->game->own_ship.get_y());
        }

        // Mouvements pour tous les missiles tirés du vaisseau ennemi courant

        int size_enemy_weapon = enemy_ship.fired_weapons.size();

        for (int j = 0; j < size_enemy_weapon; ++j) {
            Weapon *fired_weapon = enemy_ship.fired_weapons[j];

            if (fired_weapon->in_area_limit()) {
                fired_weapon->move();

                // Si collision entre Own ship et un missile ennemi
                if (this->game->check_collision(this->game->own_ship, *fired_weapon)) {
                    Mix_PlayChannel(-1, this->game->own_ship.destroy_sound, 0);

                    // Points de vie de Own ship moins la force de l'arme
                    int life = this->game->own_ship.get_health() - fired_weapon->get_strength();

                    this->game->own_ship.set_health(life);

                    enemy_ship.fired_weapons.erase(enemy_ship.fired_weapons.begin() + j);

                    // Si Own ship est détruit
                    if (!this->game->own_ship.alive()) {
                        return;
                    }

                    break;
                }
            }
            else {
                enemy_ship.fired_weapons.erase(enemy_ship.fired_weapons.begin() + j);
                break;
            }
        }

        // Si Own ship est détruit
        if (!this->game->own_ship.alive()) {
            return;
        }

        int size_ownship_weapon = this->game->own_ship.fired_weapons.size();

        for (int k = 0; k < size_ownship_weapon; ++k) {
            Weapon *fired_weapon = this->game->own_ship.fired_weapons[k];

            // Si un missile Own Ship touche un Enemy Ship
            if (this->game->check_collision(*fired_weapon, enemy_ship)) {
                // Augmente les points du joueur
                this->game->update_score(5);

                enemy_ship.set_health(0);
                continue;
            }
        }

        // Si un des Enemy Ships touche Own Ship
        if (this->game->own_ship.alive() && this->game->check_collision(this->game->own_ship, enemy_ship)) {
            // Les 2 vaisseaux sont détruits
            enemy_ship.set_health(0);
            this->game->own_ship.set_health(0);
        }
    }

    // Déplacements de Own ship et de ses missiles

    if (this->game->own_ship.alive()) {
        this->game->own_ship.move();

        int size = this->game->own_ship.fired_weapons.size();

        for (int i = 0; i < size; ++i) {
            Weapon *fired_weapon = this->game->own_ship.fired_weapons[i];

            fired_weapon->move();

            if (!fired_weapon->in_area_limit()) {
                this->game->own_ship.fired_weapons.erase(this->game->own_ship.fired_weapons.begin() + i);
            }
        }
    }
}

void LevelTwo::render() {
     SDL_RenderClear(this->game->get_window().renderer);

    // Image de background
    SDL_RenderCopy(this->game->get_window().renderer, this->texture, NULL, NULL);

    // Render des informations du jeu
    this->game->render_score();
    this->game->render_life();
    this->game->render_level();

    int dead_ships = 0;

    for (EnemyShip& enemy_ship : this->enemy_ships) {
        if (!enemy_ship.alive()) {
            // LOGI("Enemy ship - not alive");
            // Méthode d'affichage de la destruction
            this->game->render_destroy(enemy_ship);

            dead_ships++;

            if (dead_ships == this->enemy_ships.size()) {
                this->game->next_level = true;
            }
        }

        enemy_ship.render(this->game->get_window().renderer);
    }

    // Vérifie que le Own ship n'a toujours pas explosé
    if ( this->game->own_ship.get_status() != STATUS_DESTROY_END ) {
        // S'il n'est plus en vie, on gère l'animation de l'explosion
        if ( !this->game->own_ship.alive() ) {
            // Méthode d'affichage de la destruction
            this->game->render_destroy(this->game->own_ship);
        }

        this->game->own_ship.render(this->game->get_window().renderer);
    }
    else {
        // Affiche l'écran GameOver
        this->game->render_over();
    }

    SDL_RenderPresent(this->game->get_window().renderer);

    SDL_Delay(10);
}
