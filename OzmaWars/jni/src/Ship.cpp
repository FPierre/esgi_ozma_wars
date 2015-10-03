#include "Ship.h"

Ship::Ship() {

}

Ship::Ship(int _x, int _y, int _health, Sprite *_image) : x(_x),
                                                          y(_y),
                                                          health(_health),
                                                          image(_image) {
}

Ship::Ship(const Ship& _ship) {
    x = _ship.x;
    y = _ship.y;
    health = _ship.health;
    image = _ship.image;
}

Ship::~Ship() {

}

void Ship::render(SDL_Renderer *renderer) {
    this->image->render(renderer);
}
