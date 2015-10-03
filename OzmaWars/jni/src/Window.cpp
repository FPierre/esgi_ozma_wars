#include "Window.h"

Window::Window(SDL_Window *_screen, SDL_Renderer *_renderer) : screen(_screen),
                                                               renderer(_renderer) {
    SDL_GetWindowSize(this->screen, &(this->w), &(this->h));
}
