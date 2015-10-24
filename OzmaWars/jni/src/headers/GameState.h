#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
    public:
    virtual ~GameState() {};
    virtual void handle_events() = 0;
    virtual void logic() = 0;
    virtual void render() = 0;
};

#endif
