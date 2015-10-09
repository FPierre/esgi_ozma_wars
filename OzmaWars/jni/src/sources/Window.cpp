#include <android/log.h>

#include "headers/Window.h"

#define LOG_TAG "Window"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


// TODO Utiliser SDL_GetWindowSize
Window::Window() {
    SDL_Window *screen;
    SDL_Renderer *renderer;

    this->screen = screen;
    this->renderer = renderer;

    // SDL_GetWindowSize(this->screen, &(this->w), &(this->h));
    this->w = 1920;
    this->h = 1080;
}

Window::Window(const Window& _window) {
    w = _window.w;
    h = _window.h;
    screen = _window.screen;
    renderer = _window.renderer;
}

Window::~Window() {

}
