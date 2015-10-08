#include <android/log.h>

#include "headers/Window.h"

#define LOG_TAG "Window"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

Window::Window() {

}

// TODO Utiliser SDL_GetWindowSize
Window::Window(SDL_Window *_screen, SDL_Renderer *_renderer) : screen(_screen),
                                                               renderer(_renderer) {
    // SDL_GetWindowSize(this->screen, &(this->w), &(this->h));
    this->w = 1920;
    this->h = 1080;
}
