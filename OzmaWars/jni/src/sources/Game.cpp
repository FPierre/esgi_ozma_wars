#include <android/log.h>

#include "headers/Game.h"

#define LOG_TAG "Game"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

Game::Game() {
 LOGI("Constructeur trivial");
}

Game::Game(int _score, Window _window) : score(_score),
                                         window(_window) {

                                             LOGI("Constructeur");
    // TTF_Font *test = TTF_OpenFont("fonts/consola.ttf", 20);

    Rgb blue_background(0, 255, 255);
    Sprite missile_image(55, 390, 50, 20, 0.0, "spritesheets/projectile.bmp", blue_background, this->window.renderer);

    if (&missile_image != nullptr) {
        this->missile_image = missile_image;
    }
    else {
        LOGI("Sprite missile_image n'a pas pu être crée");
    }

    Rgb pink_background(255, 0, 255);
    Sprite enemy_ship_image(155, 303, 30, 28, 180.0, "spritesheets/ship.bmp", pink_background, this->window.renderer);

    if (&enemy_ship_image != nullptr) {
        this->enemy_ship_image = enemy_ship_image;
    }
    else {
        LOGI("Sprite enemy_ship_image n'a pas pu être crée");
    }

    Sprite ship_image(41, 42, 40, 45, 0.0, "spritesheets/ship.bmp", pink_background, this->window.renderer);

    if (&ship_image != nullptr) {
        this->ship_image = ship_image;
    }
    else {
        LOGI("Sprite missile_image n'a pas pu être crée");
    }

    // Rgb blue_background(0, 255, 255);
    // Sprite missile_image(55, 390, 50, 20, 0.0, "spritesheets/projectile.bmp", blue_background, this->window.renderer);

    Weapon canon(100, &(this->missile_image));

    // Rgb pink_background(255, 0, 255);
    // Sprite ship_image(155, 303, 30, 28, 180, "spritesheets/ship.bmp", pink_background, this->window.renderer);

    Ship ship(500, 500, 100, canon, &(this->ship_image));

    this->ship = ship;
}

Game::Game(const Game& _game) {
 LOGI("Constructeur par copie");

    score = _game.score;
    font = _game.font;
    window = _game.window;
    ship = _game.ship;
    missile_image = _game.missile_image;
    enemy_ship_image = _game.enemy_ship_image;
    ship_image = _game.ship_image;
}

Game::~Game() {

}

/**
 * @param int points Points à rajouter en plus du score actuel.
 */
int Game::update_score(int points) {
    return this->score += points;
}

void Game::render_score() {

// TTF_Init();
// TTF_Font *font = TTF_OpenFont("fonts/consola.ttf", 30);
// SDL_Color text_color = { 0, 0, 0 };
// SDL_Surface *message = TTF_RenderText_Solid(font, "test", text_color);
// SDL_Texture* texture = SDL_CreateTextureFromSurface(this->window.renderer, message);
// int mWidth = message->w;
// int mHeight = message->h;
// SDL_Rect test = { 10, 10, mWidth, mHeight };

// SDL_RenderCopy(this->window.renderer, texture, NULL, &test);



// TTF_CloseFont(font);
// TTF_Quit();
}
