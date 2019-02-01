#ifndef TEA_ENGINE_H
#define TEA_ENGINE_H

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "assets.h"
#include "module.h"
#include "platform.h"
#include "utils.h"

typedef struct WrenVM     WrenVM;
typedef struct WrenHandle WrenHandle;
typedef struct SDL_Window SDL_Window;
typedef void*             SDL_GLContext;

namespace Tea {
    class Engine {
    public:
        Engine();
        ~Engine();
        static std::unique_ptr<Engine> init();

        AssetManager&    get_assets();
        ScriptingBinder& get_binder();
        Platform&        get_platform();

        int run();

        template <class T>
        void add_module() {
            static_assert(std::is_base_of<Module, T>::value, "get_module() type parameter must be Module");

            if (this->modules.find(std::type_index(typeid(T))) != this->modules.end())
                throw std::runtime_error("attempted to add duplicate module type");

            this->modules.emplace(std::type_index(typeid(T)), new T(*this));
        }

        template <class T>
        T* get_module() {
            static_assert(std::is_base_of<Module, T>::value, "get_module() type parameter must be Module");

            auto res = this->modules.find(std::type_index(typeid(T)));
            if (res != this->modules.end()) {
                return dynamic_cast<T*>(&*res->second);
            }
            return nullptr;
        }

    private:
        std::unique_ptr<Platform> platform;

        WrenVM*         vm;
        WrenHandle*     prelude_class_handle;
        WrenHandle*     prelude_update_method_handle;
        ScriptingBinder binder;

        AssetManager   assets;

        std::unordered_map<std::type_index, std::unique_ptr<Module>> modules;
    };
}

#endif