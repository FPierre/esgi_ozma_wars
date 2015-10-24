#ifndef GAME_H
#define GAME_H

#include <string>
#include <map>
#include "SDL_ttf.h"

#include "Rgb.h"
#include "OwnShip.h"
#include "Sprite.h"
#include "Window.h"

class Game {
    private:
    int score;
    TTF_Font *font;
    Window window;

    public:
    Sprite missile_image;
    Sprite enemy_ship_image;
    Sprite own_ship_image;
    Sprite own_ship_image_left;
    Sprite own_ship_image_right;
    OwnShip own_ship;
    Game();
    Game(int _score, Window _window);
    Game(const Game& _game);
    ~Game();
    int update_score(int points);
    void render_score();
};

#endif
