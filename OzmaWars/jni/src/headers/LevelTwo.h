#ifndef LEVELTWO_H
#define LEVELTWO_H

#include <vector>
#include "SDL.h"

#include "Game.h"
#include "GameState.h"
#include "Window.h"
#include "EnemyShip.h"
#include "Weapon.h"

class LevelTwo : public GameState {
    private:
    Game *game;
    std::vector<EnemyShip> enemy_ships;
    SDL_Surface *background;
    SDL_Texture *texture;

    public:
    LevelTwo();
    LevelTwo(Game *_game);
    LevelTwo(const LevelTwo& _level_two);
    ~LevelTwo();
    void handle_events();
    void logic();
    void render();
};

#endif
