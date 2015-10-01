#include "math.h"
#include "star.h"
#include "SDL.h"

Star *star_init(SDL_Renderer *renderer, RGBA bg, int size, int x, int y) {
    Star *star = malloc(sizeof(Star));
    star->w = size;
    star->h = size;
    star->x = x;
    star->y = y;
    SDL_Rect star_rect = { x, y, size, size };
    star->rect = star_rect;
    SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderFillRect(renderer, &star->rect);
    star->bg.r = bg.r;
    star->bg.g = bg.g;
    star->bg.b = bg.b;
    star->bg.a = bg.a;
    return star;
}

void star_move(SDL_Renderer *renderer, Star *star, int x, int y) {
	star->x += x;
	star->y += y;
	star->rect.x += x;
	star->rect.y += y;
    SDL_SetRenderDrawColor(renderer, star->bg.r, star->bg.b, star->bg.b, star->bg.a);
    SDL_RenderFillRect(renderer, &star->rect);
}