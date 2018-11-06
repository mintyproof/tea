#include "engine.h"

#include <SDL.h>
#include <toml/toml.h>

#include <cstring>
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

        if (window == nullptr) {
            std::cerr << "Error initializing creating SDL window: " << SDL_GetError() << std::endl;
            exit(1);
        }

        // Draw to fill the framebuffer, just once
        SDL_Surface* surf = SDL_GetWindowSurface(window);
        SDL_FillRect(surf, nullptr, SDL_MapRGB(surf->format, 255, 0, 0));

        return window;
    }

    void wren_stdout(WrenVM* vm, const char* text) { std::cout << text << std::flush; }

    void wren_error(WrenVM* vm, WrenErrorType type, const char* module, int line, const char* message) {
        if (type == WrenErrorType::WREN_ERROR_COMPILE) {
            std::cerr << "Compilation error (" << module << "@" << line << "): " << message << std::endl;
        } else if (type == WrenErrorType::WREN_ERROR_RUNTIME) {
            std::cerr << "Runtime error: " << message << std::endl;
        } else if (type == WrenErrorType::WREN_ERROR_STACK_TRACE) {
            std::cerr << "    at " << module << "@" << line << ": " << message << std::endl;
        }
    }

    char* wren_load_module(WrenVM* vm, const char* name) {
        std::ostringstream filename;
        filename << name << ".wren";

        auto engine = static_cast<Engine*>(wrenGetUserData(vm));
        auto asset  = engine->get_assets().find_asset(filename.str());

        if (asset == nullptr) return nullptr;

        // Using raw C-style memory management here to make sure Wren can take ownership
        return strndup(reinterpret_cast<const char*>(&asset->get_data().front()), asset->get_data().size());
    }

    WrenVM* init_wren() {
        WrenConfiguration config;
        wrenInitConfiguration(&config);
        // TODO: set up VM hooks and whatnot
        config.writeFn      = &wren_stdout;
        config.errorFn      = &wren_error;
        config.loadModuleFn = &wren_load_module;

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

    AssetManager& Engine::get_assets() { return this->assets; }

    int Engine::run() {
        std::cout << "Starting up." << std::endl;

        // First find the main module specificed in the manifest
        auto separator_index = this->manifest.main.rfind('.');
        auto module_name     = this->manifest.main.substr(0, separator_index);
        auto class_name      = this->manifest.main.substr(separator_index + 1);

        // Then run the prelude with the main class
        std::ostringstream exec_prelude_code;
        exec_prelude_code << "import \"tea/prelude\" for Prelude\n";
        exec_prelude_code << "import \"" << module_name << "\" for " << class_name << "\n";
        exec_prelude_code << "Prelude.run(" << class_name << ")";

        auto interpret_result = wrenInterpret(this->vm, "_init", exec_prelude_code.str().c_str());
        if (interpret_result != WrenInterpretResult::WREN_RESULT_SUCCESS) {
            exit(1);
        }

        // Then get a reusable call handle for Prelude::update that we can use
        wrenEnsureSlots(this->vm, 1);
        wrenGetVariable(this->vm, "tea/prelude", "Prelude", 0);
        this->prelude_class_handle         = wrenGetSlotHandle(this->vm, 0);
        this->prelude_update_method_handle = wrenMakeCallHandle(this->vm, "update(_)");

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

            // Call the update method in Prelude
            wrenEnsureSlots(this->vm, 2);
            wrenSetSlotHandle(this->vm, 0, this->prelude_class_handle);
            wrenSetSlotDouble(this->vm, 1, delta);
            wrenCall(this->vm, this->prelude_update_method_handle);

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