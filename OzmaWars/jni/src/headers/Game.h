#ifndef GAME_H
#define GAME_H

#include <string>
#include <map>
#include "SDL_ttf.h"

#include "Rgb.h"
#include "Ship.h"
#include "Sprite.h"
#include "Window.h"

class Game {
    private:
    int score;
    TTF_Font *font;
    std::map<std::string, Sprite> sprites;
    Window window;
    Ship ship;

    public:
    Game(int _score, Window _window);
    ~Game();
    Sprite get_sprite(std::string _name);
    int update_score(int points);
    void render_score();
};

#endif
