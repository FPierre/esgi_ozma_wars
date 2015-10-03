#include "headers/Weapon.h"

Weapon::Weapon() {

}

Weapon::Weapon(int _strength, Sprite *_image) : strength(_strength),
                                                image(_image) {

}

Weapon::Weapon(const Weapon& _weapon) {
    strength = _weapon.strength;
    image = _weapon.image;
}

Weapon::~Weapon() {

}
void Weapon::render(SDL_Renderer *_renderer) {
    this->image->render(_renderer);
}

void Weapon::move(int _x, int _y) {

}
