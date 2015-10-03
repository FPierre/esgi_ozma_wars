#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "GameState.h"
#include "Window.h"
#include "Ship.h"

class LevelTwo : public GameState {
    private:
    Window window;
    Ship ship;

    public:
    LevelTwo(Window _window);
    ~LevelTwo();
    void handle_events();
    void logic();
    void render();
};

#endif
