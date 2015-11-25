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
    TTF_Font *font_title;
    SDL_Color text_black;
    SDL_Color text_red;
    Window window;

    public:
    Mix_Music *music;
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
    void render_life();
    void render_score();
    void render_destroy(Ship& _ship);
    void render_over();

    // Template pour la gestion de collisions
    // TODO Passer par des références ?
    template<class S1, class S2>
    bool check_collision( S1 a, S2 b ) {
        // Initialisation des variables
        int leftA,   leftB;
        int rightA,  rightB;
        int topA,    topB;
        int bottomA, bottomB;

        // Calcule les côtés du 1er objet (A)
        leftA =     a.get_x();
        rightA =    leftA + a.get_sprite().get_width();
        topA =      a.get_y();
        bottomA =   topA + a.get_sprite().get_height();

        // Calcule les côtés du 2nd objet (B)
        leftB =     b.get_x();
        rightB =    leftB + b.get_sprite().get_width();
        topB =      b.get_y();
        bottomB =   topB + b.get_sprite().get_height();

        // Si un seul des côtés de B est hors zone A, alors il n'y a pas de collision possible
        if( bottomB <= topA ) { /*LOGI("A");*/ return false; }
        if( topB >= bottomA ) { /*LOGI("B");*/ return false; }
        if( rightB <= leftA ) { /*LOGI("C");*/ return false; }
        if( leftB >= rightA ) { /*LOGI("D");*/ return false; }

        // Si aucun des côtés de B est hors zone A, alors il y a collision
        return true;
    }
};

#endif
