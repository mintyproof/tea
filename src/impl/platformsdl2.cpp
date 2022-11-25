#include "impl/platformsdl2.h"

#include <SDL.h>
#include "impl/renderergl33.h"

// helper macro for running SDL functions that may fail and return a null result.
//
// var  = output variable to write to should the SDL function succeed
// func = name of the SDL function to be called
// ...  = the arguments to be passed to the given SDL function
#define TEA_SDLCHECK(var, func, ...) \
    var = func(__VA_ARGS__); \
    if (var == NULL) { \
        printf("SDL error (%s at line %d): %s", __FILE_NAME__, __LINE__, SDL_GetError()); \
        exit(1); \
    }

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
    TEA_SDLCHECK(window, SDL_CreateWindow, window_title.c_str(),
                 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                 800, 600,
                 SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);

    quit = false;
}

PlatformSDL2::~PlatformSDL2() {
    SDL_DestroyWindow(window);

    platform_count -= 1;
    if (platform_count == 0) {
        SDL_Quit();
    }
}

uint64_t PlatformSDL2::runtime_milliseconds() const {
    return SDL_GetTicks64() - ticks_at_init;
}

double PlatformSDL2::runtime_seconds() const {
    uint64_t performance_counter_now = SDL_GetPerformanceCounter();
    uint64_t frequency = SDL_GetPerformanceFrequency();
    return static_cast<double>(performance_counter_now - performance_counter_at_init) / static_cast<double>(frequency);
}

void PlatformSDL2::poll_events() {
    SDL_Event sdl_event;
    while (SDL_PollEvent(&sdl_event) != 0) {
        if (sdl_event.type == SDL_QUIT) {
            quit = true;
        }
    }
}

bool PlatformSDL2::should_quit() const {
    return quit;
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

RendererGL33 PlatformSDL2::make_renderer_gl33() {
#ifdef TEA_DEBUG
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_RELEASE_BEHAVIOR, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_CreateContext(window); // TODO: this needs to be destroyed on PlatformSDL2 exit

    RendererGL33Config config;
    config.func_load_proc = SDL_GL_GetProcAddress;
    config.func_get_drawable_width = [&] {
        int w;
        SDL_GL_GetDrawableSize(window, &w, NULL);
        return w;
    };
    config.func_get_drawable_height = [&] {
        int h;
        SDL_GL_GetDrawableSize(window, &h, NULL);
        return h;
    };
    config.func_vsync_disable = [&] {
        SDL_GL_SetSwapInterval(0);
    };
    config.func_vsync_enable = [&] {
        SDL_GL_SetSwapInterval(0);
    };
    config.func_swap_buffers = [&] {
        SDL_GL_SwapWindow(window);
    };

    return RendererGL33(config);
}

}