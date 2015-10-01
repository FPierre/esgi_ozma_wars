#ifndef STAR_H
#define STAR_H

#include "SDL.h"

typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} RGBA;

typedef struct {
    int w;
    int h;
    int x;
    int y;
    SDL_Rect rect;
    RGBA bg;
} Star;

Star *star_init(SDL_Renderer *renderer, RGBA bg, int size, int x, int y);
void star_move(SDL_Renderer *renderer, Star *star, int x, int y);

#endif