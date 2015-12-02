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
    int level;
    TTF_Font *font;
    TTF_Font *font_title;
    SDL_Color text_black;
    SDL_Color text_white;
    SDL_Color text_red;
    Window window;

    public:
    static int user_id;
    static int user_score;
    static int user_life;
    static int user_level;

    bool next_level;
    bool apocalyse_now;
    Mix_Music *music;
    Sprite meteorite_image;
    Sprite missile_image;
    Sprite enemy_ship_image;
    Sprite own_ship_image;
    Sprite own_ship_image_left;
    Sprite own_ship_image_right;
    Sprite destroyed_ship_image_step1;
    Sprite destroyed_ship_image_step2;
    Sprite destroyed_ship_image_step3;
    Sprite destroyed_ship_image_step4;
    OwnShip own_ship;
    Game();
    Game(Window _window);
    Game(const Game& _game);
    ~Game();
    Window get_window();
    int get_score();
    void set_score(int _points);
    int update_score(int _points);
    int get_level();
    void set_level(int _level);
    void render_life();
    void render_score();
    void render_level();
    void render_destroy(Ship& _ship);
    void render_over();

    // Template pour la gestion de collisions
    template<class S1, class S2>
    bool check_collision( S1 a, S2 b ) {
        // Calcule les côtés du 1er objet (A)
        int left_a   = a.get_x();
        int top_a    = a.get_y();
        int right_a  = left_a + a.get_sprite().get_width();
        int bottom_a = top_a + a.get_sprite().get_height();

        // Calcule les côtés du 2nd objet (B)
        int left_b   = b.get_x();
        int top_b    = b.get_y();
        int right_b  = left_b + b.get_sprite().get_width();
        int bottom_b = top_b + b.get_sprite().get_height();

        // Si un seul des côtés de B est hors zone A, alors il n'y a pas de collision possible
        if (bottom_b <= top_a || top_b >= bottom_a || right_b <= left_a || left_b >= right_a) {
            return false;
        }

        // Si aucun des côtés de B est hors zone A, alors il y a collision
        return true;
    }
};

#endif
