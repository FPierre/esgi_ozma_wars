#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"

typedef struct {
    int r;
    int g;
    int b;
} RGB;

typedef struct {
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect image_location;
} Sprite;

Sprite *sprite_init(SDL_Renderer *renderer, char *path, RGB background, int x, int y, int w, int h);
void sprite_render(SDL_Renderer *renderer, Sprite *sprite);
void sprite_position(Sprite *sprite, int x, int y);

#endif
