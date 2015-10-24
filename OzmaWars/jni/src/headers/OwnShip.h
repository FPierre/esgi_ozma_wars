#ifndef OWNSHIP_H
#define OWNSHIP_H

#include "Ship.h"

// TODO Transformer en Singleton ?
class OwnShip : public Ship {
    public:
    OwnShip();
    OwnShip(int _x, int _y, int _health, Weapon _weapon, Sprite *_image);
    OwnShip(const OwnShip& _ship);
    ~OwnShip();
    void move();
};

#endif
