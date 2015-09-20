#ifndef WEAPON_H
#define WEAPON_H

#define PI 3.14159265

// typedef struct {
//     // int type;
//     // struct Object ?
//     int x;
//     int y;
//     Ship ship;
// } Target;

typedef struct {
    int strength;
    int speed;
} Weapon;

Weapon *weapon_init(int strength);
// void fire(Weapon *weapon, Target *target);

#endif
