#include "engine.h"

#include <toml/toml.h>
#include <wren.hpp>

#include <cstring>
#include <iostream>

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

    void wren_stdout(WrenVM*, const char* text) { std::cout << text << std::flush; }

    void wren_error(WrenVM*, WrenErrorType type, const char* module, int line, const char* message) {
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
        size_t size = asset->get_data().size();
        char*  data = static_cast<char*>(malloc(size + 1));
        data[size]  = '\0';
        memcpy(data, reinterpret_cast<const char*>(&asset->get_data().front()), size);
        return data;
    }

    WrenForeignMethodFn wren_bind_foreign_fn(WrenVM*     vm,
                                             const char* module,
                                             const char* className,
                                             bool        isStatic,
                                             const char* signature) {
        auto engine = static_cast<Engine*>(wrenGetUserData(vm));
        return engine->get_binder().resolve_function(isStatic, module, className, signature);
    }

    WrenVM* init_wren() {
        WrenConfiguration config;
        wrenInitConfiguration(&config);
        // TODO: set up VM hooks and whatnot
        config.writeFn             = &wren_stdout;
        config.errorFn             = &wren_error;
        config.loadModuleFn        = &wren_load_module;
        config.bindForeignMethodFn = &wren_bind_foreign_fn;

        WrenVM* vm = wrenNewVM(&config);
        return vm;
    }

    Engine::Engine(): renderer(Renderer(*this)) {}

    Engine::~Engine() {
        std::cout << "Quitting engine:" << std::endl;
        std::cout << "| Freeing memory" << std::endl;
        wrenFreeVM(this->vm);

        std::cout << "Bye." << std::endl;
    }

    std::unique_ptr<Engine> Engine::init() {
        std::cout << "Initializing engine.." << std::endl;

        auto vm = init_wren();
        auto mf = load_manifest();

        std::unique_ptr<Engine> engine(new Engine());
        engine->vm       = vm;
        engine->manifest = mf;
        engine->platform = Platform::init();

        Renderer::bind(engine->binder);
        engine->renderer.init();

        // Now that we have a persistent pointer to Engine, set it as the Wren userdata
        // So the scripting stuff can access the rest of the engine
        wrenSetUserData(engine->vm, engine.get());
        return engine;
    }

    AssetManager&    Engine::get_assets() { return this->assets; }
    ScriptingBinder& Engine::get_binder() { return this->binder; }
    Platform&        Engine::get_platform() { return *(this->platform); }
    Renderer&        Engine::get_renderer() { return this->renderer; }

    int Engine::run() {
        std::cout << "Starting up." << std::endl;

        // First find the main module specificed in the manifest
        auto separator_index = this->manifest.main.rfind(".");
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

        this->platform->main_loop([this](double delta) {
            this->get_renderer().begin();

            // Call the update method in Prelude
            wrenEnsureSlots(this->vm, 2);
            wrenSetSlotHandle(this->vm, 0, this->prelude_class_handle);
            wrenSetSlotDouble(this->vm, 1, delta);
            wrenCall(this->vm, this->prelude_update_method_handle);

            this->get_renderer().flush();
        });

        return 0;
    }
}
