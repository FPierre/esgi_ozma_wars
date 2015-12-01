#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "Ship.h"

class EnemyShip : public Ship {
    private:
    int propability_fire;   // Probabilité que le vaisseau fasse feu lors d'un tour (en %)
    int fired_weapon_limit;
    int size_coeff;
    bool can_fire();

    public:
    EnemyShip();
    EnemyShip(int _x, int _y, int _health, int _status, Weapon _weapon, Sprite _image, int screen_width, int screen_height);
    void fire(int _x, int _y);
    void set_destination(int _x, int _y);
    void move();
};

#endif
