#include "Window.h"

Window::Window(SDL_Renderer *_renderer, SDL_Window *_screen) : renderer(_renderer),
                                                               screen(_screen) {
    SDL_GetWindowSize(this->screen, &(this->w), &(this->h));
}
