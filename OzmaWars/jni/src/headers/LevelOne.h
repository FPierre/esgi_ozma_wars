#ifndef LEVELONE_H
#define LEVELONE_H

#include <vector>
#include "SDL.h"

#include "Game.h"
#include "GameState.h"
#include "Window.h"
#include "Ship.h"
#include "Weapon.h"

class LevelOne : public GameState {
    private:
    Game game;
    Window window;
    std::vector<Ship> ships;

    public:
    LevelOne();
    LevelOne(Game _game, Window _window);
    LevelOne(const LevelOne& _level_one);
    ~LevelOne();
    void handle_events();
    void logic();
    void render();
};

#endif
