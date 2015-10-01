#include "sprite.h"

Sprite *sprite_init(SDL_Renderer *renderer, char *path, RGB background, int x, int y, int w, int h) {
    Sprite *sprite = malloc(sizeof(Sprite));
    sprite->surface = SDL_LoadBMP(path);
    //SDL_SetColorKey(sprite->surface, SDL_TRUE, SDL_MapRGB(sprite->surface->format, background.r, background.g, background.b));
    sprite->texture = SDL_CreateTextureFromSurface(renderer, sprite->surface);
    sprite->image_location.x = x;
    sprite->image_location.y = y;
    sprite->image_location.w = w;
    sprite->image_location.h = h;

    return sprite;
}

void sprite_render(SDL_Renderer *renderer, Sprite *sprite) {
    SDL_Rect test = { 100, 100, 100, 100 };
    SDL_RenderCopy(renderer, sprite->texture, &(sprite->image_location), &test);
}

void sprite_position(Sprite *sprite, int x, int y) {
    sprite->image_location.x = x;
    sprite->image_location.y = y;
}