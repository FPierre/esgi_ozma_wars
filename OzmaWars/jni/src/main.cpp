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

// Etapes possibles du jeu
enum GameStates {
    STATE_NULL,
    STATE_LEVEL_ONE,
    STATE_LEVEL_TWO,
    STATE_EXIT
};

// Gestion des étapes du jeu
int state_id = STATE_NULL;
int next_state = STATE_NULL;

GameState *current_state = NULL;

void set_next_state(int newState);
void change_state(Game *game);

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

    // Récupération des dimensions de l'écran
    int w, h;
    SDL_GetWindowSize(window.screen, &w, &h);
    window.set_width(w);
    window.set_height(h);

    // Initialisation du jeu
    Game *game = new Game(window);

    Uint8 done = 0;
    SDL_Event event;

    // Initialisation du 1er niveau de jeu
    state_id = STATE_LEVEL_ONE;
    current_state = new LevelOne(game);

    game->set_level(1);

    // Boucle principale
    while (state_id != STATE_EXIT) {
        // Sortie de jeu
        if (!game->own_ship.alive() || game->force_exit) {
            set_next_state(STATE_EXIT);
        }

        current_state->handle_events();
        current_state->logic();

        current_state->render();

        if (game->own_ship.alive() && (state_id == STATE_LEVEL_ONE && game->get_score() >= 10) || game->next_level) {
            set_next_state(STATE_LEVEL_TWO);
            change_state(game);
            game->set_level(2);
            game->next_level = false;
        }
    }

    TTF_Quit();

    exit(0);
}

void set_next_state(int new_state) {
    if (next_state != STATE_EXIT) {
        next_state = new_state;
    }
}

void change_state(Game *game) {
    if (next_state != STATE_NULL) {
        if (next_state != STATE_EXIT) {
            delete current_state;
        }

        switch (next_state) {
            case STATE_LEVEL_ONE:
                current_state = new LevelOne(game);
                break;

            case STATE_LEVEL_TWO:
                current_state = new LevelTwo(game);
                break;
        }

        state_id = next_state;
        next_state = STATE_NULL;
    }
}
