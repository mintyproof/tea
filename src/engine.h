#ifndef TEA_ENGINE_H
#define TEA_ENGINE_H

#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>

#include "assets.h"
#include "module.h"
#include "platform.h"
#include "scripting.h"
#include "utils.h"

namespace Tea {
    class Engine {
    public:
        Engine();
        ~Engine();
        AssetManager& get_assets();
        Scripting&    get_scripting();
        Platform&     get_platform();

        int run(std::string main_module, std::string main_class);

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

        AssetManager               assets;
        std::unique_ptr<Scripting> scripting;

        std::unordered_map<std::type_index, std::unique_ptr<Module>> modules;
    };
}

#endif