#include "impl/platformsdl2.h"

#include <SDL.h>

namespace tea {

unsigned int PlatformSDL2::platform_count = 0;

PlatformSDL2::PlatformSDL2() {
    if (platform_count == 0) {
        SDL_Init(SDL_INIT_TIMER
                 | SDL_INIT_AUDIO
                 | SDL_INIT_VIDEO
                 | SDL_INIT_EVENTS);
    }
    platform_count += 1;

    ticks_at_init = SDL_GetTicks64();
    performance_counter_at_init = SDL_GetPerformanceCounter();

    window_title = "Tea";
    window = SDL_CreateWindow(window_title.c_str(),
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              800, 600,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
}

PlatformSDL2::~PlatformSDL2() {
    SDL_DestroyWindow(window);

    platform_count -= 1;
    if (platform_count == 0) {
        SDL_Quit();
    }
}

int PlatformSDL2::window_get_width() const {
    int w;
    SDL_GetWindowSize(window, &w, NULL);
    return w;
}

int PlatformSDL2::window_get_height() const {
    int h;
    SDL_GetWindowSize(window, NULL, &h);
    return h;
}

int PlatformSDL2::window_get_drawable_width() const {
    return 0;
}

int PlatformSDL2::window_get_drawable_height() const {
    return 0;
}

std::string_view PlatformSDL2::window_get_title() const {
    return window_title;
}

void PlatformSDL2::window_set_size(int width, int height) {
    SDL_SetWindowSize(window, width, height);
}

void PlatformSDL2::window_set_title(const std::string& title) {
    window_title = title;
    SDL_SetWindowTitle(window, window_title.c_str());
}

SDL_Window* PlatformSDL2::get_raw_window() {
    return window;
}

uint64_t PlatformSDL2::runtime_milliseconds() const {
    return SDL_GetTicks64() - ticks_at_init;
}

double PlatformSDL2::runtime_seconds() const {
    uint64_t performance_counter_now = SDL_GetPerformanceCounter();
    uint64_t frequency = SDL_GetPerformanceFrequency();
    return static_cast<double>(performance_counter_now - performance_counter_at_init) / static_cast<double>(frequency);
}

}