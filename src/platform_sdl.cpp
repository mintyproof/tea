#include <memory>

#include "platform_sdl.h"

#include <iostream>

#include <glad/glad.h>

namespace Tea {
    PlatformSDLGraphics::PlatformSDLGraphics(PlatformSDL& platform): platform(platform) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

        this->gl = SDL_GL_CreateContext(this->platform.window);
        if (this->gl == nullptr) {
            std::cerr << "Error creating OpenGL context: " << SDL_GetError() << std::endl;
            exit(1);
        }

        gladLoadGLES2Loader(SDL_GL_GetProcAddress);
    }

    PlatformSDLGraphics::~PlatformSDLGraphics() noexcept = default;

    void PlatformSDLGraphics::resize(uint32_t width, uint32_t height) {}

    uint32_t PlatformSDLGraphics::get_width() const noexcept {
        int w, h;
        SDL_GetWindowSize(this->platform.window, &w, &h);
        return static_cast<uint32_t>(w);
    }

    uint32_t PlatformSDLGraphics::get_height() const noexcept {
        int w, h;
        SDL_GetWindowSize(this->platform.window, &w, &h);
        return static_cast<uint32_t>(h);
    }

    PlatformSDLInput::PlatformSDLInput(PlatformSDL& platform): platform(platform), key_callback([](int, KeyState) {}) {}
    PlatformSDLInput::~PlatformSDLInput() noexcept = default;

    void PlatformSDLInput::set_key_callback(std::function<void(int, KeyState)> cb) noexcept { this->key_callback = cb; }

    PlatformSDL::PlatformSDL() {
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

        if (this->window == nullptr) {
            std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
            exit(1);
        }

        this->graphics = std::make_unique<PlatformSDLGraphics>(*this);
        this->input    = std::make_unique<PlatformSDLInput>(*this);
    }

    PlatformSDL::~PlatformSDL() noexcept {
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }

    PlatformGraphics& PlatformSDL::get_graphics() noexcept { return *this->graphics; }
    PlatformInput&    PlatformSDL::get_input() noexcept { return *this->input; }

    void PlatformSDL::main_loop(std::function<void(double)> update_function) {
        bool     quit        = false;
        uint64_t last_update = SDL_GetPerformanceCounter();

        while (!quit) {
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_KEYDOWN) {
                    if (!e.key.repeat) {
                        this->input->key_callback(e.key.keysym.scancode, PlatformInput::KeyState::Pressed);
                    }
                } else if (e.type == SDL_KEYUP) {
                    this->input->key_callback(e.key.keysym.scancode, PlatformInput::KeyState::Released);
                }
            }

            // Calculate delta time
            uint64_t this_update = SDL_GetPerformanceCounter();
            double   delta       = (double)((this_update - last_update)) / (double)SDL_GetPerformanceFrequency();
            last_update          = this_update;

            update_function(delta);

            SDL_GL_SwapWindow(this->window);
        }
    }

    std::unique_ptr<Platform> Platform::init() { return std::unique_ptr<Platform>(new PlatformSDL()); }
}