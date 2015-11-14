#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include "SDL.h"

#include "Weapon.h"
#include "Sprite.h"

// TODO Transformer en virtuelle pure ?
// TODO Utiliser des getter/setter
class Ship {
    protected:
    int x;
    int y;
    int length_x;
    int length_y;
    int destination_x;      // Point x de destination du vaisseau
    int destination_y;      // Point y de destination du vaisseau
    int health;             // Points de vie du vaisseau
    int status;             // Statut pour la destruction d'un vaisseau
    Sprite *image;
    SDL_Rect area_limits;   // Zone de laquelle le vaisseau ne peut pas sortir
    int fired_weapon_limit; // Nombre maximum de missiles tirés sans qu'ils ne soit détruits en mémoire

    public:
    std::vector<Weapon*> fired_weapons;
    Weapon weapon;
    Ship();
    Ship(int _x, int _y, int _health, int _status, Weapon _weapon, Sprite *_image);
    Ship(const Ship& _ship);
    ~Ship();
    int get_x();
    int get_y();
    Sprite *get_sprite();
    void set_sprite(Sprite *_image);
    int get_health();
    void set_health(int _health);
    int get_status();
    void set_status(int _status);
    void dec_status(int _status);
    bool alive();
    void render(SDL_Renderer *_renderer);
    virtual void move() = 0;
};

#endif
