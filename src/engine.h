#include <memory>

#include "assets.h"
#include "renderer.h"
#include "utils.h"

typedef struct WrenVM     WrenVM;
typedef struct WrenHandle WrenHandle;
typedef struct SDL_Window SDL_Window;
typedef void*             SDL_GLContext;

namespace Tea {
    struct EngineManifest {
        std::string main;
    };

    class Engine {
    public:
        ~Engine();
        static std::unique_ptr<Engine> init();

        AssetManager&    get_assets();
        ScriptingBinder& get_binder();

        int run();

    private:
        void init_sdl();

        SDL_Window*   window;
        SDL_GLContext gl_context;

        WrenVM*         vm;
        WrenHandle*     prelude_class_handle;
        WrenHandle*     prelude_update_method_handle;
        ScriptingBinder binder;

        AssetManager   assets;
        Renderer       renderer;
        EngineManifest manifest;
    };
}