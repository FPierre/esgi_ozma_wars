#include <android/log.h>
#include <jni.h>
#include "android/sensor.h"
#include "../sdl/src/core/android/SDL_android.h"
#include "SDL.h"
#include <string>

#include "headers/Window.h"
#include "headers/Rgb.h"
#include "headers/Sprite.h"
#include "headers/Weapon.h"
#include "headers/Ship.h"
#include "headers/GameState.h"
#include "headers/LevelOne.h"
#include "headers/LevelTwo.h"

enum GameStates {
    STATE_NULL,
    STATE_LEVEL_ONE,
    STATE_LEVEL_TWO,
    STATE_EXIT
};

int state_id = STATE_NULL;
int next_state = STATE_NULL;

GameState *current_state = NULL;

// State status manager
void set_next_state(int newState);

// State changer
void change_state(Window window);

int main(int argc, char *argv[]) {
    SDL_Window *screen;
    SDL_Renderer *renderer;
    Window window(screen, renderer);

    if (SDL_CreateWindowAndRenderer(0, 0, 0, &(window.screen), &(window.renderer)) < 0) {
        exit(2);
    }

    Uint8 done = 0;
    SDL_Event event;

    // Rgb blue_background(0, 255, 255);
    // Sprite missile_image(55, 390, 50, 20, 0.0, "spritesheets/projectile.bmp", blue_background, window.renderer);
    // Weapon canon(100, &missile_image);

    // Rgb pink_background(255, 0, 255);
    // Sprite ship_image(41, 42, 40, 45, 0.0, "spritesheets/ship.bmp", pink_background, window.renderer);
    // Ship ship(0, 0, 100, &ship_image);

    // Set the current state ID
    state_id = STATE_LEVEL_ONE;

    // Set the current game state object
    current_state = new LevelOne(window);

    // While the user hasn't quit
    while (state_id != STATE_EXIT) {
        // Do state event handling
        current_state->handle_events();
        // Do state logic
        current_state->logic();
        // Change state if needed
        change_state(window);
        // Do state rendering
        current_state->render();


    // while (!done) {
        // while (SDL_PollEvent(&event)) {
        //     switch (event.type) {
        //         case SDL_QUIT: case SDL_KEYDOWN:
        //             done = 1;
        //             break;
        //     }
        // }

        // SDL_RenderClear(window.renderer);

        // ship.render(window.renderer);

        // SDL_SetRenderDrawColor(window.renderer, 35, 226, 35, SDL_ALPHA_OPAQUE);
        // // SDL_SetRenderDrawColor(window.renderer, 226, 35, 35, SDL_ALPHA_OPAQUE);
        // SDL_RenderPresent(window.renderer);

        // SDL_Delay(10);
    }

    // SDL_DestroyTexture(tex);
    // SDL_DestroyTexture(tex2);

    exit(0);
}

void set_next_state(int newState) {
    // If the user doesn't want to exit
    if (next_state != STATE_EXIT) {
        //Set the next state
        next_state = newState;
    }
}


void change_state(Window window) {
    // If the state needs to be changed
    if (next_state != STATE_NULL) {
        // Delete the current state
        if (next_state != STATE_EXIT) {
            delete current_state;
        }

        // Change the state
        switch (next_state) {
            case STATE_LEVEL_ONE:
                current_state = new LevelOne(window);
                break;

            case STATE_LEVEL_TWO:
                current_state = new LevelTwo(window);
                break;
        }

        // Change the current state ID
        state_id = next_state;
        // NULL the next state ID
        next_state = STATE_NULL;
    }
}
