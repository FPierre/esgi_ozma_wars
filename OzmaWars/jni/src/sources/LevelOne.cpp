#include <android/log.h>
#include "SDL.h"

#include "headers/LevelOne.h"
#include "headers/Game.h"
#include "headers/Sprite.h"

#define LOG_TAG "LevelOne"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

const int STATUS_NORMAL      = 80;
const int STATUS_DESTROY_END = 0;

LevelOne::LevelOne(Game *_game) : game(_game) {
    this->background = SDL_LoadBMP("images/background_level_one.bmp");

    if (this->background == NULL) {
        LOGI("Sprite non trouve");
        LOGI("%s\n", SDL_GetError());
        exit(0);
    }

    LOGI("%d", this->meteorite->get_x());
    LOGI("%d", this->meteorite->get_y());
    LOGI("%d", this->meteorite->get_sprite().get_height());
    LOGI("%d", this->meteorite->get_sprite().get_height());

    this->texture = SDL_CreateTextureFromSurface(this->game->get_window().renderer, this->background);
    this->image_location = { 0, 0, this->game->get_window().get_width(), this->game->get_window().get_height() };
    this->test = { 0, 0, this->game->get_window().get_width(), this->game->get_window().get_height() };

    int screen_width = this->game->get_window().get_width();
    int screen_height = this->game->get_window().get_height();

    Weapon canon(20, this->game->missile_image, screen_width, screen_height);

    EnemyShip enemy_ship_1(0, 0, 100, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_1);

    EnemyShip enemy_ship_2(-50, 200, 100, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_2);

    EnemyShip enemy_ship_3(-600, 80, 100, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_3);

    EnemyShip enemy_ship_4(-840, 370, 100, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_4);

    EnemyShip enemy_ship_5(-1200, 40, 100, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_5);

    EnemyShip enemy_ship_6(-2300, 230, 100, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_6);

    EnemyShip enemy_ship_7(-2500, 400, 100, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_7);

    EnemyShip enemy_ship_8(-3000, 270, 100, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_8);

    EnemyShip enemy_ship_9(-3800, 100, 100, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_9);

    EnemyShip enemy_ship_10(-4500, 290, 100, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_10);

    EnemyShip enemy_ship_11(-4800, 70, 100, STATUS_NORMAL, canon, this->game->enemy_ship_image, screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_11);

    // S'il n'y a pas encore de musique jouée
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(this->game->music, -1);
    }
}

LevelOne::LevelOne(const LevelOne& _level_one) {
    game = _level_one.game;
    enemy_ships = _level_one.enemy_ships;
    background = _level_one.background;
    texture = _level_one.texture;
    image_location = _level_one.image_location;
    test = _level_one.test;
    meteorite = _level_one.meteorite;
}

LevelOne::~LevelOne() {

}

void LevelOne::handle_events() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        // Si "tap" sur l'écran, Own ship tire
        if (this->game->own_ship.alive() && event.type == SDL_FINGERDOWN) {
            this->game->own_ship.fire();
        } else if (event.type == SDL_KEYDOWN) {
            this->game->force_exit = true;
        }
    }
}

void LevelOne::logic() {
    int random_number_meteorite = rand() % 101;

    if (random_number_meteorite < 1 && !this->game->apocalyse_now) {
        Meteorite *meteorite = new Meteorite(this->game->meteorite_image,
                                             this->game->get_window().get_width(),
                                             this->game->get_window().get_height());

        meteorite->set_x(1200);
        meteorite->set_y(-200);
        meteorite->set_destination(200, 1000);

        this->meteorite = meteorite;

        this->game->apocalyse_now = true;
    }

    if (this->game->apocalyse_now) {
        this->meteorite->move();
    }

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
                    Game::user_life = life;

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

        if (this->game->apocalyse_now && this->game->check_collision(*meteorite, enemy_ship)) {
            enemy_ship.set_health(0);
            continue;
        }

        // Si un des Enemy Ships touche Own Ship
        if (this->game->own_ship.alive() && this->game->check_collision(this->game->own_ship, enemy_ship)) {
            // Les 2 vaisseaux sont détruits
            enemy_ship.set_health(0);
            this->game->own_ship.set_health(0);
        }
    }

    // Collision entre Own ship et la météorite
    if (this->game->apocalyse_now && this->game->check_collision(this->game->own_ship, *meteorite)) {
        this->game->own_ship.set_health(0);
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

void LevelOne::render() {
    SDL_RenderClear(this->game->get_window().renderer);

    // Image de background
    SDL_RenderCopy(this->game->get_window().renderer, this->texture, NULL, NULL);

    // Render des informations du jeu
    this->game->render_score();
    this->game->render_life();
    this->game->render_level();

    if (this->game->apocalyse_now) {
        // Render du météorite
        this->meteorite->render(this->game->get_window().renderer);
    }

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
