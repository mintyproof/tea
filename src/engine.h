#include <memory>

#include <SDL.h>

#include "assets.h"

typedef struct WrenVM WrenVM;

namespace Tea {
    struct EngineManifest {
        std::string main;
    };

    class Engine {
    public:
        ~Engine();
        static std::unique_ptr<Engine> init();

        AssetManager& get_assets();

        int run();

    private:
        SDL_Window* window;
        WrenVM*     vm;

        AssetManager   assets;
        EngineManifest manifest;
    };
}