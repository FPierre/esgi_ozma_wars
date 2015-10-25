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
    SDL_Color text_color;
    Window window;

    public:
    Sprite missile_image;
    Sprite enemy_ship_image;
    Sprite own_ship_image;
    Sprite own_ship_image_left;
    Sprite own_ship_image_right;
    Sprite explosion_image;
    OwnShip own_ship;
    Game();
    Game(int _score, Window _window);
    Game(const Game& _game);
    ~Game();
    int get_score();
    int update_score(int points);
    void render_life();
    void render_score();
};

#endif
