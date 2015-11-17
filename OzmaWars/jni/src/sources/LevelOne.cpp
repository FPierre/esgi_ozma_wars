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

LevelOne::LevelOne(Game _game, Window _window) : game(_game),
                                                 window(_window) {
    // LOGI("Constructeur");

    int screen_width = this->window.get_width();
    int screen_height = this->window.get_height();

    Weapon canon(100, &(this->game.missile_image), screen_width, screen_height);

    OwnShip own_ship(200, 550, 100, STATUS_NORMAL, canon, &(this->game.own_ship_image),
                                                           &(this->game.own_ship_image_left),
                                                           &(this->game.own_ship_image_right),
                                                           screen_width, screen_height);
    this->game.own_ship = own_ship;

    // Ennemi 1
    EnemyShip enemy_ship_1(80, 350, 100, STATUS_NORMAL, canon, &(this->game.enemy_ship_image), screen_width, screen_height);
    enemy_ship_1.set_destination(screen_width, 0);
    this->enemy_ships.push_back(enemy_ship_1);

    // Ennemi 2
    EnemyShip enemy_ship_2(100, 100, 100, STATUS_NORMAL, canon, &(this->game.enemy_ship_image), screen_width, screen_height);
    enemy_ship_2.set_destination(screen_width, 200);
    this->enemy_ships.push_back(enemy_ship_2);
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
        // Si "tap" sur l'écran, Own ship tire
        if (event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN) {
            if (this->game.own_ship.fire()) {
                // TODO Mieux encapsuler cette méthode
                Mix_PlayChannel(-1, this->game.own_ship.weapon.launch_sound, 0);
            }
        }
    }
}

void LevelOne::logic() {
    // Vérification des status des vaisseaux et des collisions
    for (EnemyShip& enemy_ship : this->enemy_ships) {
        // Si le vaisseau est mort, on le retire du vector
        if (!enemy_ship.alive() && enemy_ship.get_status() == STATUS_DESTROY_END) {
            // On déplace l'item en dernière place
            std::swap(enemy_ship, this->enemy_ships.back());
            // On le supprime du vector
            this->enemy_ships.pop_back();
        }
        // S'il n'est pas en train d'être détruit, on exécute les actions
        else if (enemy_ship.alive() && enemy_ship.get_status() == STATUS_NORMAL) {
            enemy_ship.move();

            int random_number = rand() % 100 + 1;

            if (random_number < enemy_ship.get_propability_fire()) {
                // Vise Own ship
                enemy_ship.fire(this->game.own_ship.get_x(), this->game.own_ship.get_y());
            }

            // Pour tous les missiles tirés du vaisseau ennemi
            for (Weapon *fired_weapon : enemy_ship.fired_weapons) {
                fired_weapon->move();

                // if (fired_weapon->y <= 0) {
                //     delete fired_weapon;
                // }
            }
        }


        // Si le Own Ship est mort, on évite les calculs pour tous
        if ( !this->game.own_ship.alive() )
            break;

        // Si le vaisseau ennemi n'a plus de vie, on passe au suivant
        if ( !enemy_ship.alive() )
            continue;

        // Si un missile du Own Ship touche un Enemy Ship
        // TODO Enlever le missile du vector
        for (Weapon *fired_weapon : this->game.own_ship.fired_weapons) {
            if ( this->game.check_collision(*fired_weapon, enemy_ship) ) {
                LOGI("Collision between own weapon and enemy ship");
                enemy_ship.set_health(0);
                // On augmente les points du joueur
                this->game.update_score(5);
                LOGI("Score: %d", this->game.get_score());

                // TODO Détruire le missile
                break;
            }
        }

        // Si un missile des Enemy Ships touche le Own Ship
        // TODO Enlever le missile du vector
        for (Weapon *fired_weapon : enemy_ship.fired_weapons) {
            if ( this->game.check_collision(this->game.own_ship, *fired_weapon) ) {
                LOGI("Collision between enemy weapon and own ship");
                this->game.own_ship.set_health(0);
                // TODO Mieux encapsuler cette méthode
                // TODO Vérifier selon les points de vie de Own ship (selon la force de l'arme qui les touche,
                //      il ne perd pas forcément tous ses points de vie)
                Mix_PlayChannel(-1, this->game.own_ship.destroy_sound, 0);
                
                // TODO Détruire le missile
                break;
            }
        }

        // Si un des Enemy Ships touche le Own Ship
        if ( this->game.check_collision(this->game.own_ship, enemy_ship) ) {
            LOGI("Collision between enemy and own ships");
            enemy_ship.set_health(0);
            this->game.own_ship.set_health(0);
        }
    }

    // Mouvements des objets seulement si encore en vie
    if ( this->game.own_ship.alive() ) {
        this->game.own_ship.move();
    }

    // Pour tous les missiles tirés par Own ship
    for (Weapon *fired_weapon : this->game.own_ship.fired_weapons) {
        fired_weapon->move();

        // if (fired_weapon->y <= 0) {
        //     delete fired_weapon;
        // }
    }

    // this->enemy_ships[0].move();
    // this->enemy_ships[0].weapon.move();

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

    for (EnemyShip& enemy_ship : this->enemy_ships) {
        LOGI("Health of enemy ship: %d", enemy_ship.get_health());
        if ( !enemy_ship.alive() ) {
            LOGI("Enemy ship - not alive");
            // Méthode d'affichage de la destruction
            this->game.render_destroy(enemy_ship);
        }
        LOGI("Enemy ship - render");
        // Render du Sprite
        enemy_ship.render(this->window.renderer);
    }

    // On vérifie que le Ship n'a toujours pas explosé
    if ( this->game.own_ship.get_status() != STATUS_DESTROY_END ) {
        // S'il n'est plus en vie, on gère l'animation de l'explosion
        if ( !this->game.own_ship.alive() ) {
            // Méthode d'affichage de la destruction
            this->game.render_destroy(this->game.own_ship);
        }
        // Render du Sprite
        this->game.own_ship.render(this->window.renderer);
    } else {
        // On affiche l'écran GameOver
        this->game.render_over();
    }

    // SDL_SetRenderDrawColor(this->window.renderer, 226, 35, 35, SDL_ALPHA_OPAQUE);
    // SDL_SetRenderDrawColor(this->window.renderer, 35, 226, 35, SDL_ALPHA_OPAQUE);
    SDL_SetRenderDrawColor(this->window.renderer, 35, 35, 226, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(this->window.renderer);

    SDL_Delay(100);
}
