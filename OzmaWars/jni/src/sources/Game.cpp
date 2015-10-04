#include "headers/Game.h"

Game::Game(int _score, Window _window) : score(_score),
                                         window(_window) {
    Rgb blue_background(0, 255, 255);
    Sprite missile_image(55, 390, 50, 20, 0.0, "spritesheets/projectile.bmp", blue_background, window.renderer);
    this->sprites["missile"] = missile_image;

    Rgb pink_background(255, 0, 255);
    Sprite ship_image(155, 303, 30, 28, 180.0, "spritesheets/ship.bmp", pink_background, window.renderer);
    this->sprites["ship"] = ship_image;
}

Game::~Game() {

}

Sprite Game::get_sprite(std::string _name) {
    if (this->sprites.find(_name) != this->sprites.end()) {
        return this->sprites[_name];
    }
}

/**
 * @param int points Points à rajouter en plus du score actuel.
 */
int Game::update_score(int points) {
    return this->score += points;
}

void Game::render_score() {

}
