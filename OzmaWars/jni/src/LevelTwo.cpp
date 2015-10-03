#include "SDL.h"

#include "LevelTwo.h"
#include "Rgb.h"
#include "Sprite.h"
#include "Ship.h"

LevelTwo::LevelTwo(Window _window) : window(_window) {
    // Init de tous les objets

    // Rgb pink_background(255, 0, 255);
    // Sprite ship_image(41, 42, 40, 45, 0.0, "spritesheets/ship.bmp", pink_background, window.renderer);
    // Ship ship(0, 0, 100, &ship_image);

    // this->ship = ship;
}

LevelTwo::~LevelTwo() {

}

void LevelTwo::handle_events() {
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

void LevelTwo::logic() {
    // If the dot went to the exit
    // if (check_collision(myDot, exit) == true) {
    //     // Go to the overworld
    //     set_next_state(STATE_GREEN_OVERWORLD);
    // }

    // // Move the dot
    // myDot.move();
}

void LevelTwo::render() {
    SDL_RenderClear(this->window.renderer);

    // SDL_SetRenderDrawColor(this->window.renderer, 35, 226, 35, SDL_ALPHA_OPAQUE);
    // SDL_SetRenderDrawColor(this->window.renderer, 226, 35, 35, SDL_ALPHA_OPAQUE);
    SDL_SetRenderDrawColor(this->window.renderer, 35, 35, 226, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(this->window.renderer);

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
