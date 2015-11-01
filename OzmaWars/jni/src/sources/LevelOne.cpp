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

LevelOne::LevelOne(Game _game, Window _window) : game(_game),
                                                 window(_window) {

    // LOGI("Constructeur");

    int w = this->window.get_width();

    Weapon canon(100, &(this->game.missile_image));

    OwnShip own_ship(200, 550, 100, 4, canon, &(this->game.own_ship_image),
                                            &(this->game.own_ship_image_left),
                                            &(this->game.own_ship_image_right));
    this->game.own_ship = own_ship;

    EnemyShip enemy_ship_1(80, 350, 100, 4, canon, &(this->game.enemy_ship_image));
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
    // Vérification des status des vaisseaux
    for (int i = 0; i != this->enemy_ships.size(); ++i) {
        // Si le vaisseau est mort, on le retire du vector
        if (!this->enemy_ships[i].alive() && this->enemy_ships[i].get_status() == 0) {
            this->enemy_ships.erase(this->enemy_ships.begin() + i);
        }
    }

    // Vérification des collisions
    for (EnemyShip enemy_ship : this->enemy_ships) {
        // Si le Own Ship est mort, on évite les calculs pour tous
        if ( !this->game.own_ship.alive() )
            break;

        // Si le vaisseau ennemi n'a plus de vie, on passe au suivant
        if ( !enemy_ship.alive() )
            continue;

        // Si un missile du Own Ship touche un Enemy Ship
        if ( this->game.check_collision(this->game.own_ship.weapon, enemy_ship) ) {
            LOGI("Collision between own weapon and enemy ship");
            enemy_ship.set_health(0);
        }

        // Si un missile des Enemy Ships touche le Own Ship
        if ( this->game.check_collision(this->game.own_ship, enemy_ship.weapon) ) {
            LOGI("Collision between enemy weapon and own ship");
            this->game.own_ship.set_health(0);
        }

        // Si un des Enemy Ships touche le Own Ship
        if ( this->game.check_collision(this->game.own_ship, enemy_ship) ) {
            LOGI("Collision between enemy and own ships");
            enemy_ship.set_health(0);
            this->game.own_ship.set_health(0);
        }
    }

    // Mouvements des objets
    this->game.own_ship.move();

    // this->enemy_ships[0].move();
    // this->enemy_ships[0].weapon.move();

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
// SDL_Color text_color = { 255, 255, 255 };
// SDL_Surface *message = TTF_RenderText_Solid(font, "test", text_color);
// SDL_Texture* texture = SDL_CreateTextureFromSurface(this->window.renderer, message);
// int mWidth = message->w;
// int mHeight = message->h;
// SDL_Rect test = { 10, 10, mWidth, mHeight };

// SDL_RenderCopy(this->window.renderer, texture, NULL, &test);

    this->game.render_score();
    this->game.render_life();

    for (EnemyShip enemy_ship : this->enemy_ships) {
        if ( enemy_ship.get_health() == 0 ) {
            // Méthode d'affichage de la destruction
            this->game.render_destroy(enemy_ship);
        }
        // Render du Sprite
        enemy_ship.render(this->window.renderer, enemy_ship.get_sprite());
    }
    
/** NOT WORKING **/
    // if ( !this->game.own_ship.alive() ) {
    //     // Méthode d'affichage de la destruction
    //     this->game.render_destroy(this->game.own_ship);
    // }

    // Render du Sprite
    this->game.own_ship.render(this->window.renderer, this->game.own_ship.get_sprite());

    // SDL_SetRenderDrawColor(this->window.renderer, 226, 35, 35, SDL_ALPHA_OPAQUE);
    SDL_SetRenderDrawColor(this->window.renderer, 35, 226, 35, SDL_ALPHA_OPAQUE);
    // SDL_SetRenderDrawColor(this->window.renderer, 35, 35, 226, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(this->window.renderer);

    SDL_Delay(1000);
}
