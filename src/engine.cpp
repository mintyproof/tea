#include "engine.h"
#include "modules/input.h"
#include "modules/renderer.h"

#include <wren.hpp>

#include <cstring>
#include <iostream>
#include <sstream>

namespace Tea {
    Engine::Engine() {
        std::cout << "Initializing engine.." << std::endl;
        this->scripting = std::unique_ptr<Scripting>(new Scripting(*this));
        this->platform = Platform::init();

        this->add_module<Input>();
        this->add_module<Renderer>();

        for (auto& module : this->modules) {
            module.second->bind(*this->scripting);
        }
    }

    Engine::~Engine() { std::cout << "Bye." << std::endl; }

    AssetManager& Engine::get_assets() { return this->assets; }
    Platform& Engine::get_platform() { return *(this->platform); }
    Scripting& Engine::get_scripting() { return *(this->scripting); }

    int Engine::run(std::string main_module, std::string main_class) {
        this->scripting->init(main_module, main_class);

        this->platform->main_loop([this](double delta) {
            for (auto& module : this->modules) {
                module.second->pre_update();
            }

            this->scripting->update(delta);

            for (auto& module : this->modules) {
                module.second->post_update();
            }
        });

        return 0;
    }
}
