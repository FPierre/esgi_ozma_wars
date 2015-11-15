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
    OwnShip(int _x, int _y, int _health, int _status, Weapon _weapon, Sprite *_image, Sprite *_image_left, Sprite *_image_right, int screen_width, int screen_height);
    OwnShip(const OwnShip& _ship);
    ~OwnShip();
    bool fire();
    void move();
};

#endif
