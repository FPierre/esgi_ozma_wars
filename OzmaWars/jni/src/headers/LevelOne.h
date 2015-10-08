#ifndef LEVELONE_H
#define LEVELONE_H

#include <vector>
#include "SDL.h"

#include "Game.h"
#include "GameState.h"
#include "Window.h"
#include "Ship.h"

// TESTS
#include "Weapon.h"

class LevelOne : public GameState {
    private:
    Game game;
    Window window;
    std::vector<Ship> ships;
    std::map<std::string, Sprite> sprites;

    public:
    LevelOne(Game _game, Window _window);
    ~LevelOne();
    void handle_events();
    void logic();
    void render();
};

#endif
