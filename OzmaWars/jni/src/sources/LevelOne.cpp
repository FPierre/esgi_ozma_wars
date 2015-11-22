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

LevelOne::LevelOne(Game _game) : game(_game) {
    // LOGI("Constructeur");

    this->background = SDL_LoadBMP("images/background.bmp");

    if (this->background == NULL) {
        LOGI("Sprite non trouve");
        LOGI("%s\n", SDL_GetError());
        exit(0);
    }

    this->texture = SDL_CreateTextureFromSurface(this->game.get_window().renderer, this->background);
    this->image_location = { 0, 0, 1920, 1080 };
    this->test = { 0, 0, 1920, 1080};

    int screen_width = this->game.get_window().get_width();
    int screen_height = this->game.get_window().get_height();

    Weapon canon(100, &(this->game.missile_image), screen_width, screen_height);

    EnemyShip enemy_ship_1(0, 0, 100, STATUS_NORMAL, canon, &(this->game.enemy_ship_image), screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_1);

    EnemyShip enemy_ship_2(-50, 200, 100, STATUS_NORMAL, canon, &(this->game.enemy_ship_image), screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_2);

    EnemyShip enemy_ship_3(-600, 80, 100, STATUS_NORMAL, canon, &(this->game.enemy_ship_image), screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_3);

    EnemyShip enemy_ship_4(-840, 370, 100, STATUS_NORMAL, canon, &(this->game.enemy_ship_image), screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_4);

    EnemyShip enemy_ship_5(-1200, 40, 100, STATUS_NORMAL, canon, &(this->game.enemy_ship_image), screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_5);

    EnemyShip enemy_ship_6(-2300, 230, 100, STATUS_NORMAL, canon, &(this->game.enemy_ship_image), screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_6);

    EnemyShip enemy_ship_7(-2500, 400, 100, STATUS_NORMAL, canon, &(this->game.enemy_ship_image), screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_7);

    EnemyShip enemy_ship_8(-3000, 270, 100, STATUS_NORMAL, canon, &(this->game.enemy_ship_image), screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_8);

    EnemyShip enemy_ship_9(-3800, 100, 100, STATUS_NORMAL, canon, &(this->game.enemy_ship_image), screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_9);

    EnemyShip enemy_ship_10(-4500, 290, 100, STATUS_NORMAL, canon, &(this->game.enemy_ship_image), screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_10);

    EnemyShip enemy_ship_11(-4800, 70, 100, STATUS_NORMAL, canon, &(this->game.enemy_ship_image), screen_width, screen_height);
    this->enemy_ships.push_back(enemy_ship_11);
}

LevelOne::LevelOne(const LevelOne& _level_one) {
    // LOGI("Constructeur par copie");

    game = _level_one.game;
    enemy_ships = _level_one.enemy_ships;
    background = _level_one.background;
    texture = _level_one.texture;
    image_location = _level_one.image_location;
    test = _level_one.test;
}

LevelOne::~LevelOne() {

}

void LevelOne::handle_events() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        // Si "tap" sur l'écran, Own ship tire
        if (event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN) {
            this->game.own_ship.fire();
        }
    }
}

void LevelOne::logic() {

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

    // // Déplacement sur x doit être plus important que déplacement sur y
    // int random_number_for_x = rand() % 5 + 1;
    // uint min = -10;
    // uint max = 1;
    // int random_number_for_y = min + (rand() % (int)(max - min + 1));

    // // LOGI("random_number_for_y : %d", random_number_for_y);

    // int test1 = random_number_for_x + this->enemy_ships[0].get_x();
    // int test2 = random_number_for_y + this->enemy_ships[0].get_y();

    // // LOGI("test2 : %d", test2);

    // this->enemy_ships[0].set_destination(test1, test2);
    // this->enemy_ships[0].move();






    // // Vérification des status des vaisseaux et des collisions
    // for (std::vector<EnemyShip>::iterator it_enemy = this->enemy_ships.begin();
    //             it_enemy != this->enemy_ships.end(); ++it_enemy) {
    // // for (EnemyShip& enemy_ship : this->enemy_ships) {
    //     // LOGI("------- ''IN'' Nombre de enemy : %d", this->enemy_ships.size());

    //     EnemyShip& enemy_ship = *it_enemy;

    //     // Si le vaisseau ennemi est mort et qu'il n'a pas de missile en cours, on le retire du vector
    //     if (!enemy_ship.alive() && enemy_ship.get_status() == STATUS_DESTROY_END
    //             && enemy_ship.fired_weapons.size() == 0) {

    //         // TODO: automatiser à l'aide d'un template ?
    //         this->enemy_ships.erase(it_enemy);

    //         // // On déplace l'item en dernière place
    //         // std::swap(enemy_ship, this->enemy_ships.back());
    //         // // On le supprime du vector
    //         // this->enemy_ships.pop_back();
    //     }
    //     // S'il n'est pas en train d'être détruit, on exécute les actions
    //     else if (enemy_ship.alive() && enemy_ship.get_status() == STATUS_NORMAL) {
    //         enemy_ship.move();

    //         int random_number = rand() % 100 + 1;

    //         if (enemy_ship.can_fire(random_number)) {
    //             // Vise Own ship
    //             enemy_ship.fire(this->game.own_ship.get_x(), this->game.own_ship.get_y());
    //         }
    //     }

    //     // LOGI("------- ''OUT'' Nombre de enemy : %d", this->enemy_ships.size());

    //     // Mouvements pour tous les missiles tirés du vaisseau ennemi
    //     // TODO Pour la limite de destruction des missiles, se servir de la limit_area et de ses méthodes dans Weapon
    //     for (Weapon *fired_weapon : enemy_ship.fired_weapons) {
    //         if (fired_weapon->x < 0
    //             || fired_weapon->y < 0
    //             || fired_weapon->x > this->game.get_window().get_width()
    //             || fired_weapon->y > this->game.get_window().get_height()) {
    //             // LOGI("Weapon dies()");
    //             delete fired_weapon;
    //         } else {
    //             // LOGI("Weapon moves()");
    //             fired_weapon->move();
    //         }
    //     }

    //     // Si le Own Ship est mort, on évite les calculs pour tous
    //     if ( !this->game.own_ship.alive() )
    //         break;

    //     // Si un missile des Enemy Ships touche le Own Ship
    //     // TODO Enlever le missile du vector
    //     for (Weapon *fired_weapon : enemy_ship.fired_weapons) {
    //         if ( this->game.check_collision(this->game.own_ship, *fired_weapon) ) {
    //             // LOGI("Collision between enemy weapon and own ship");
    //             this->game.own_ship.set_health(0);
    //             // TODO Mieux encapsuler cette méthode
    //             // TODO Vérifier selon les points de vie de Own ship (selon la force de l'arme qui les touche,
    //             //      il ne perd pas forcément tous ses points de vie)
    //             Mix_PlayChannel(-1, this->game.own_ship.destroy_sound, 0);

    //             // TODO Automatiser à l'aide d'un template ?
    //             // this->game.remove_item( *fired_weapon, enemy_ship.fired_weapons );

    //             // // On déplace l'item en dernière place
    //             // std::swap(*fired_weapon, *(enemy_ship.fired_weapons.back()));
    //             // // On le supprime du vector
    //             // enemy_ship.fired_weapons.pop_back();
    //             delete fired_weapon;
    //             break;
    //         }
    //     }

    //     // Si le vaisseau ennemi n'a plus de vie, on passe au suivant
    //     if ( !enemy_ship.alive() )
    //         continue;

    //     // Si un missile du Own Ship touche un Enemy Ship
    //     // TODO Enlever le missile du vector
    //     for (Weapon *fired_weapon : this->game.own_ship.fired_weapons) {
    //         if ( this->game.check_collision(*fired_weapon, enemy_ship) ) {
    //             // LOGI("Collision between own weapon and enemy ship");
    //             enemy_ship.set_health(0);
    //             // On augmente les points du joueur
    //             this->game.update_score(5);
    //             // LOGI("Score: %d", this->game.get_score());

    //             // TODO Automatiser à l'aide d'un template ?
    //             // this->game.remove_item( *fired_weapon, this->game.own_ship.fired_weapons );

    //             // On déplace l'item en dernière place
    //             // std::swap(fired_weapon, this->game.own_ship.fired_weapons.back());
    //             // // On le supprime du vector
    //             // this->game.own_ship.fired_weapons.pop_back();
    //             delete fired_weapon;
    //             break;
    //         }
    //     }

    //     // Si un des Enemy Ships touche le Own Ship
    //     if ( this->game.check_collision(this->game.own_ship, enemy_ship) ) {
    //         // LOGI("Collision between enemy and own ships");
    //         enemy_ship.set_health(0);
    //         this->game.own_ship.set_health(0);
    //     }
    // }

    // // Mouvements des objets seulement si encore en vie
    // if ( this->game.own_ship.alive() ) {
    //     this->game.own_ship.move();
    // }

    // // Pour tous les missiles tirés par Own ship
    // for (Weapon *fired_weapon : this->game.own_ship.fired_weapons) {
    //     fired_weapon->move();

    //     // if (fired_weapon->y <= 0) {
    //     //     delete fired_weapon;
    //     // }
    // }

    // // this->enemy_ships[0].move();
    // // this->enemy_ships[0].weapon.move();

    // // Niveau suivant
    // // Pas encore effectif
    // if (this->game.get_score() > 5) {
    //     // set_next_state(STATE_LEVEL_TWO);
    // }

    // // Sortie de jeu
    // // Pas encore effectif
    // if (this->game.own_ship.alive() == false) {
    //     // set_next_state(STATE_EXIT);
    // }
}

void LevelOne::render() {
    SDL_RenderClear(this->game.get_window().renderer);

    // Image de background
    SDL_RenderCopy(this->game.get_window().renderer, this->texture, NULL, NULL);

    this->game.render_score();
    this->game.render_life();

    for (EnemyShip& enemy_ship : this->enemy_ships) {
        // LOGI("Health of enemy ship: %d", enemy_ship.get_health());
        if ( !enemy_ship.alive() ) {
            // LOGI("Enemy ship - not alive");
            // Méthode d'affichage de la destruction
            this->game.render_destroy(enemy_ship);
        }
        // LOGI("Enemy ship - render");
        // Render du Sprite
        enemy_ship.render(this->game.get_window().renderer);
    }

    // On vérifie que le Ship n'a toujours pas explosé
    if ( this->game.own_ship.get_status() != STATUS_DESTROY_END ) {
        // S'il n'est plus en vie, on gère l'animation de l'explosion
        if ( !this->game.own_ship.alive() ) {
            // Méthode d'affichage de la destruction
            this->game.render_destroy(this->game.own_ship);
        }
        // Render du Sprite
        this->game.own_ship.render(this->game.get_window().renderer);
    } else {
        // On affiche l'écran GameOver
        this->game.render_over();
    }


    // SDL_SetRenderDrawColor(this->game.get_window().renderer, 226, 35, 35, SDL_ALPHA_OPAQUE);
    // SDL_SetRenderDrawColor(this->game.get_window().renderer, 35, 226, 35, SDL_ALPHA_OPAQUE);
    // SDL_SetRenderDrawColor(this->game.get_window().renderer, 35, 35, 226, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(this->game.get_window().renderer);

    SDL_Delay(10);
}
