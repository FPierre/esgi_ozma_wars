#include <android/log.h>

#include "headers/Game.h"

#define LOG_TAG "Game"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

Game::Game(int _score) : score(_score) {
    // TTF_Font *test = TTF_OpenFont("fonts/consola.ttf", 20);
}

Game::~Game() {

}

void Game::set_window(Window _window) {
    this->window = _window;
}

void Game::init_sprites() {
    Rgb blue_background(0, 255, 255);
    Sprite missile_image(55, 390, 50, 20, 0.0, "spritesheets/projectile.bmp", blue_background, window.renderer);
    this->sprites["missile"] = missile_image;

    Rgb pink_background(255, 0, 255);
    Sprite ship_image(155, 303, 30, 28, 180.0, "spritesheets/ship.bmp", pink_background, window.renderer);
    this->sprites["ship"] = ship_image;
}

Sprite Game::get_sprite(std::string _name) {
    if (this->sprites.find(_name) != this->sprites.end()) {
        return this->sprites[_name];
    }
    else {
        LOGI("Sprite non trouve");
        exit(0);
    }
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
