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

    public:
    Game(int _score);
    ~Game();
    void set_window(Window _window);
    void init_sprites();
    Sprite get_sprite(std::string _name);
    int update_score(int points);
    void render_score();
};

#endif
