#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "Ship.h"

class EnemyShip : public Ship {
    public:
    EnemyShip();
    EnemyShip(int _x, int _y, int _health, Weapon _weapon, Sprite *_image);
    // EnemyShip(const EnemyShip& _ship);
    // ~EnemyShip();
    void fire(int _x, int _y);
    void set_destination(int _x, int _y);
    void move();
};

#endif
