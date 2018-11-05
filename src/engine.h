#include <memory>

#include <SDL.h>

#include "assets.h"

typedef struct WrenVM     WrenVM;
typedef struct WrenHandle WrenHandle;

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

        WrenHandle* prelude_class_handle;
        WrenHandle* prelude_update_method_handle;

        AssetManager   assets;
        EngineManifest manifest;
    };
}