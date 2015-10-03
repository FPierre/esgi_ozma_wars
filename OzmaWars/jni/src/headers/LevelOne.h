#ifndef LEVELONE_H
#define LEVELONE_H

#include "GameState.h"
#include "Window.h"
#include "Ship.h"

class LevelOne : public GameState {
    private:
    Window window;
    Ship ship;

    public:
    LevelOne(Window _window);
    ~LevelOne();
    void handle_events();
    void logic();
    void render();
};

#endif
