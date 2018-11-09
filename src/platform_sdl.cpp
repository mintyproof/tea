#include "platform_sdl.h"

#include <iostream>

#include <glad/glad.h>

namespace Tea {
    PlatformGraphics::PlatformGraphics(Platform& platform): platform(platform) {
        this->gl = SDL_GL_CreateContext(this->platform.window);
        if (this->gl == nullptr) {
            std::cerr << "Error creating OpenGL context: " << SDL_GetError() << std::endl;
            exit(1);
        }

        gladLoadGLES2Loader(SDL_GL_GetProcAddress);

        // Draw to fill the framebuffer, just once
        SDL_Surface* surf = SDL_GetWindowSurface(this->platform.window);
        SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 255, 0, 0));
    }

    PlatformGraphics::~PlatformGraphics() {}

    PlatformInput::PlatformInput(Platform& platform): platform(platform) {}
    PlatformInput::~PlatformInput() {}

    Platform::Platform() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
            exit(1);
        }

        this->window = SDL_CreateWindow("Test Engine",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        640,
                                        480,
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

        if (this->window == NULL) {
            std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
            exit(1);
        }

        this->graphics.reset(new PlatformGraphics(*this));
        this->input.reset(new PlatformInput(*this));
    }

    Platform::~Platform() {
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }

    PlatformGraphics& Platform::get_graphics() { return *this->graphics; }
    PlatformInput&    Platform::get_input() { return *this->input; }

    void Platform::main_loop(std::function<void(double)> update_function) {
        bool     quit        = false;
        uint64_t last_update = SDL_GetPerformanceCounter();

        while (!quit) {
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }

            // Calculate delta time
            uint64_t this_update = SDL_GetPerformanceCounter();
            double   delta       = (double)((this_update - last_update)) / (double)SDL_GetPerformanceFrequency();
            last_update          = this_update;

            update_function(delta);

            SDL_UpdateWindowSurface(this->window);
        }
    }
}