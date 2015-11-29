#include <android/log.h>

#include "headers/Window.h"

#define LOG_TAG "Window"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

Window::Window() {
    SDL_Window *screen;
    SDL_Renderer *renderer;
    this->screen = screen;
    this->renderer = renderer;
}

Window::Window(const Window& _window) {
    w = _window.w;
    h = _window.h;
    screen = _window.screen;
    renderer = _window.renderer;
}

Window::~Window() {

}

int Window::get_height() {
    return this->h;
}

void Window::set_height(int _h) {
    this->h = _h;
}

int Window::get_width() {
    return this->w;
}

void Window::set_width(int _w) {
    this->w = _w;
}
