#ifndef OWNSHIP_H
#define OWNSHIP_H

#include "Ship.h"

// TODO Transformer en Singleton ?
class OwnShip : public Ship {
    private:
    Sprite *image_front;
    Sprite *image_left;
    Sprite *image_right;

    public:
    OwnShip();
    OwnShip(int _x, int _y, int _health, Weapon _weapon, Sprite *_image, Sprite *_image_left, Sprite *_image_right);
    OwnShip(const OwnShip& _ship);
    ~OwnShip();
    void fire();
    void move();
};

#endif
