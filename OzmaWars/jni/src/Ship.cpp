#include "Ship.h"

Ship::Ship() {

}

Ship::Ship(int _x, int _y, int _health, Weapon *_weapon, Sprite *_image) : x(_x),
                                                                           y(_y),
                                                                           health(_health),
                                                                           weapon(_weapon),
                                                                           image(_image) {
}

Ship::Ship(const Ship& _ship) {
    x = _ship.x;
    y = _ship.y;
    health = _ship.health;
    weapon = _ship.weapon;
    image = _ship.image;
}

Ship::~Ship() {

}

void Ship::render(SDL_Renderer *_renderer) {
    this->image->render(_renderer);
}
