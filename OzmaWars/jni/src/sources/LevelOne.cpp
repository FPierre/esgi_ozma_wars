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
    Rgb blue_background(0, 255, 255);
    Sprite missile_image(55, 390, 50, 20, 0.0, "spritesheets/projectile.bmp", blue_background, window.renderer);
    this->sprites["missile"] = missile_image;

    Rgb pink_background(255, 0, 255);
    Sprite ship_image(155, 303, 30, 28, 180, "spritesheets/ship.bmp", pink_background, window.renderer);
    this->sprites["ship"] = ship_image;

    SDL_Rect window_borders = { 0, 0, this->window.w, this->window.h };

    Weapon canon(100, &(this->sprites["missile"]));

    Ship ship1(0, 0, 100, canon, &(this->sprites["ship"]), window_borders);
    this->ships.push_back(ship1);

    Ship ship2(200, 200, 100, canon, &(this->sprites["ship"]), window_borders);
    this->ships.push_back(ship2);
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
    this->ships[0].move(200, 0);
    // this->ships[0].fire(300, 400);

    this->ships[1].move(400, 0);
    // this->ships[1].fire(700, 200);

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

    for (Ship ship : this->ships) {
        ship.render(this->window.renderer);
    }

    // SDL_SetRenderDrawColor(this->window.renderer, 226, 35, 35, SDL_ALPHA_OPAQUE);
    // SDL_SetRenderDrawColor(this->window.renderer, 35, 226, 35, SDL_ALPHA_OPAQUE);
    SDL_SetRenderDrawColor(this->window.renderer, 35, 35, 226, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(this->window.renderer);

    SDL_Delay(20);
}
