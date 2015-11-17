#include <android/log.h>
#include <jni.h>
#include "android/sensor.h"
#include "../sdl/src/core/android/SDL_android.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>

#include "headers/Game.h"
#include "headers/Window.h"
#include "headers/Rgb.h"
#include "headers/Sprite.h"
#include "headers/Weapon.h"
#include "headers/Ship.h"
#include "headers/GameState.h"
#include "headers/LevelOne.h"
#include "headers/LevelTwo.h"

// TODO Commenter
enum GameStates {
    STATE_NULL,
    STATE_LEVEL_ONE,
    STATE_LEVEL_TWO,
    STATE_EXIT
};

int state_id = STATE_NULL;
int next_state = STATE_NULL;

GameState *current_state = NULL;

void set_next_state(int newState);
void change_state(Game& game, Window& window);

#define LOG_TAG "main"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

int main(int argc, char *argv[]) {
    Window window;

    // Initialisation de la fenêtre
    if (SDL_CreateWindowAndRenderer(0, 0, 0, &(window.screen), &(window.renderer)) < 0) {
        exit(2);
    }

    // Initialisation du son
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        LOGI("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    // TODO A déplacer dans le constructeur de Window ? (bien tester !)
    int w, h;
    SDL_GetWindowSize(window.screen, &w, &h);
    // LOGI("%d", w);
    // LOGI("%d", h);

    window.set_width(w);
    window.set_height(h);

    // Initialisation du jeu, avec un score 0
    Game game(0, window);

    Uint8 done = 0;
    SDL_Event event;

    // Initialisation du 1er niveau de jeu
    state_id = STATE_LEVEL_ONE;
    current_state = new LevelOne(game, window);

    while (state_id != STATE_EXIT) {
        current_state->handle_events();
        current_state->logic();
        // change_state(game, window);
        current_state->render();
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

void change_state(Game& game, Window& window) {
    // If the state needs to be changed
    if (next_state != STATE_NULL) {
        // Delete the current state
        if (next_state != STATE_EXIT) {
            delete current_state;
        }

        // Change the state
        switch (next_state) {
            case STATE_LEVEL_ONE:
                current_state = new LevelOne(game, window);
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
