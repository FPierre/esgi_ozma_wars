#include "SDL.h"
#include "SDL_ttf.h"

#include "headers/LevelOne.h"
#include "headers/Game.h"

LevelOne::LevelOne(Window _window) : window(_window) {
    Rgb blue_background(0, 255, 255);
    Sprite missile_image(55, 390, 50, 20, 0.0, "spritesheets/projectile.bmp", blue_background, window.renderer);
    Weapon canon(100, &missile_image);

    Rgb pink_background(255, 0, 255);
    Sprite ship_image(155, 303, 30, 28, 180.0, "spritesheets/ship.bmp", pink_background, window.renderer);

    for (int i = 0; i < 3; i++) {
        Ship ship(0, 0, 100, &canon, &ship_image);

        this->ships.push_back(ship);
    }
}

LevelOne::~LevelOne() {

}

void LevelOne::handle_events() {
    SDL_Event event;

    // While there's events to handle
    while (SDL_PollEvent(&event)) {
        // Handle events for the dot
        // myDot.handle_input();

        //If the user has Xed out the window
        if (event.type == SDL_QUIT) {
            // set_next_state(STATE_EXIT);
        }
    }
}

void LevelOne::logic() {
    // this->ships[0].move(100, 100);

    // If the dot went to the exit
    // if (check_collision(myDot, exit) == true) {
    //     // Go to the overworld
    //     set_next_state(STATE_GREEN_OVERWORLD);
    // }

    // // Move the dot
    // myDot.move();
}

void LevelOne::render() {

// FONCTIONNE
// TTF_Init();

// TTF_Font *font = TTF_OpenFont("fonts/consola.ttf", 20);
// SDL_Color text_color = { 0, 0, 0 };
// SDL_Surface *message = TTF_RenderText_Solid(font, "test", text_color);
// SDL_Texture* texture = SDL_CreateTextureFromSurface(this->window.renderer, message);
// int mWidth = message->w;
// int mHeight = message->h;
// SDL_Rect test = { 10, 10, mWidth, mHeight };


    SDL_RenderClear(this->window.renderer);

    // SDL_RenderCopy(this->window.renderer, texture, NULL, &test);

    // SDL_Rect test = { 100, 100, 100, 100 };
    // SDL_RenderCopy(this->window.renderer, s.image->texture, &(s.image->image_location), &test);





    this->ships[0].render(this->window.renderer);







    SDL_SetRenderDrawColor(this->window.renderer, 35, 226, 35, SDL_ALPHA_OPAQUE);
    // SDL_SetRenderDrawColor(this->window.renderer, 226, 35, 35, SDL_ALPHA_OPAQUE);
    // SDL_SetRenderDrawColor(this->window.renderer, 35, 35, 226, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(this->window.renderer);

// TTF_CloseFont(font);
// TTF_Quit();

    SDL_Delay(10);
}
