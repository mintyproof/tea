#include <memory>

#include "assets.h"
#include "platform.h"
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
        Engine();
        ~Engine();
        static std::unique_ptr<Engine> init();

        AssetManager&    get_assets();
        ScriptingBinder& get_binder();
        Platform&        get_platform();
        Renderer&        get_renderer();

        int run();

    private:
        std::unique_ptr<Platform> platform;

        WrenVM*         vm;
        WrenHandle*     prelude_class_handle;
        WrenHandle*     prelude_update_method_handle;
        ScriptingBinder binder;

        AssetManager   assets;
        Renderer       renderer;
        EngineManifest manifest;
    };
}