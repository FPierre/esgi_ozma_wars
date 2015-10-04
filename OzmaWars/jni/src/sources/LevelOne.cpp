#include "SDL.h"
#include "SDL_ttf.h"

#include "headers/LevelOne.h"
#include "headers/Rgb.h"
#include "headers/Sprite.h"
#include "headers/Ship.h"

LevelOne::LevelOne(Window _window) : window(_window) {
    // Init de tous les objets

    // Rgb pink_background(255, 0, 255);
    // Sprite ship_image(41, 42, 40, 45, 0.0, "spritesheets/ship.bmp", pink_background, window.renderer);
    // Ship ship(0, 0, 100, &ship_image);

    // this->ship = ship;
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
    // If the dot went to the exit
    // if (check_collision(myDot, exit) == true) {
    //     // Go to the overworld
    //     set_next_state(STATE_GREEN_OVERWORLD);
    // }

    // // Move the dot
    // myDot.move();
}

void LevelOne::render() {


    // Rgb blue_background(0, 255, 255);
    // Sprite missile_image(55, 390, 50, 20, 0.0, "spritesheets/projectile.bmp", blue_background, window.renderer);
    // Weapon canon(100, &missile_image);

    // Rgb pink_background(255, 0, 255);
    // Sprite ship_image(41, 42, 40, 45, 0.0, "spritesheets/ship.bmp", pink_background, window.renderer);
    // Ship ship(0, 0, 100, &canon, &ship_image);








TTF_Init();

TTF_Font *font = TTF_OpenFont("fonts/consola.ttf", 20);
SDL_Color text_color = { 0, 0, 0 };
SDL_Surface *message = TTF_RenderText_Solid(font, "test", text_color);
SDL_Texture* texture = SDL_CreateTextureFromSurface(this->window.renderer, message);
int mWidth = message->w;
int mHeight = message->h;
SDL_Rect test = { 10, 10, mWidth, mHeight };




    // this->ship = ship;

    SDL_RenderClear(this->window.renderer);


SDL_RenderCopy(this->window.renderer, texture, NULL, &test);


    // ship.render(this->window.renderer);

    // SDL_SetRenderDrawColor(this->window.renderer, 35, 226, 35, SDL_ALPHA_OPAQUE);
    // SDL_SetRenderDrawColor(this->window.renderer, 226, 35, 35, SDL_ALPHA_OPAQUE);
    SDL_SetRenderDrawColor(this->window.renderer, 35, 35, 226, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(this->window.renderer);

TTF_CloseFont(font);
TTF_Quit();

    SDL_Delay(10);


    // // Set the camera
    // myDot.set_camera();

    // // Show the background
    // apply_surface( 0, 0, background, screen, &camera );

    // // Show the door
    // exit.show();

    // // Show the dot on the screen
    // myDot.show();
}
