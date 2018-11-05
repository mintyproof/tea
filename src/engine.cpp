#include "engine.h"

#include <SDL.h>
#include <toml/toml.h>

#include <iostream>
#include <wren.hpp>

namespace Tea {
    EngineManifest load_manifest() {
        std::ifstream     ifs("game.toml");
        toml::ParseResult pr = toml::parse(ifs);

        if (!pr.valid()) {
            std::cerr << "Error parsing manifest: " << pr.errorReason << std::endl;
            exit(1);
        }

        auto v = pr.value;

        auto mainClassValue = v.find("app.main");
        if (mainClassValue) {
            EngineManifest mf;
            mf.main = mainClassValue->as<std::string>();
            return mf;
        } else {
            std::cerr << "Manifest did not declare app.main key." << std::endl;
            exit(1);
        }
    }

    SDL_Window* init_sdl() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
            exit(1);
        }

        SDL_Window* window = SDL_CreateWindow(
            "Test Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

        if (window == NULL) {
            std::cerr << "Error initializing creating SDL window: " << SDL_GetError() << std::endl;
            exit(1);
        }

        // Draw to fill the framebuffer, just once
        SDL_Surface* surf = SDL_GetWindowSurface(window);
        SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 255, 0, 0));

        return window;
    }

    void wren_stdout(WrenVM* vm, const char* text) {
        std::cout << text;
        std::flush(std::cout);
    }

    void wren_error(WrenVM* vm, WrenErrorType type, const char* module, int line, const char* message) {
        if (type == WrenErrorType::WREN_ERROR_COMPILE) {
            std::cerr << "Compilation error (" << module << "@" << line << "): " << message;
        } else if (type == WrenErrorType::WREN_ERROR_RUNTIME) {
            std::cerr << "Runtime error (" << module << "@" << line << "): " << message;
        } else if (type == WrenErrorType::WREN_ERROR_STACK_TRACE) {
            std::cerr << "\tat " << module << "@" << line << ": " << message;
        }
    }

    WrenVM* init_wren() {
        WrenConfiguration config;
        wrenInitConfiguration(&config);
        // TODO: set up VM hooks and whatnot
        config.writeFn = &wren_stdout;
        config.errorFn = &wren_error;

        WrenVM* vm = wrenNewVM(&config);
        return vm;
    }

    std::unique_ptr<Engine> Engine::init() {
        std::cout << "Initializing engine:" << std::endl;

        std::cout << "| Initializing SDL" << std::endl;
        auto window = init_sdl();

        std::cout << "| Initializing VM state" << std::endl;
        auto vm = init_wren();

        std::cout << "| Loading manifest" << std::endl;
        auto mf = load_manifest();

        std::unique_ptr<Engine> engine(new Engine());
        engine->window   = window;
        engine->vm       = vm;
        engine->manifest = mf;

        // Now that we have a persistent pointer to Engine, set it as the Wren userdata
        // So the scripting stuff can access the rest of the engine
        wrenSetUserData(engine->vm, engine.get());
        return engine;
    }

    int Engine::run() {
        std::cout << "Starting up." << std::endl;

        bool quit = false;
        while (!quit) {
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }

            SDL_UpdateWindowSurface(this->window);
        }

        return 0;
    }

    Engine::~Engine() {
        std::cout << "Quitting engine:" << std::endl;
        std::cout << "| Freeing memory" << std::endl;
        wrenFreeVM(this->vm);

        SDL_DestroyWindow(this->window);
        SDL_Quit();

        std::cout << "Bye." << std::endl;
    }
}