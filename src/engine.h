#include <memory>

#include <SDL.h>
#include <wren.hpp>

namespace Tea {
    struct EngineManifest {
        std::string main;
    };

    class Engine {
    public:
        ~Engine();
        static std::unique_ptr<Engine> init();

        int run();

    private:
        SDL_Window*    window;
        WrenVM*        vm;
        EngineManifest manifest;
    };
}