#ifndef LEVELONE_H
#define LEVELONE_H

#include <vector>
#include "SDL.h"

#include "Game.h"
#include "GameState.h"
#include "Window.h"
#include "EnemyShip.h"
#include "Weapon.h"
#include "Meteorite.h"

class LevelOne : public GameState {
    private:
    Game *game;
    Meteorite *meteorite;
    std::vector<EnemyShip> enemy_ships;
    SDL_Surface *background;
    SDL_Texture *texture;
    SDL_Rect image_location;
    SDL_Rect test;

    public:
    LevelOne();
    LevelOne(Game *_game);
    LevelOne(const LevelOne& _level_one);
    ~LevelOne();
    void handle_events();
    void logic();
    void render();
};

#endif
