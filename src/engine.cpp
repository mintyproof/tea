#include "engine.h"

namespace tea {

Engine::Engine(std::vector<std::string> args) {
    this->args = std::move(args);
    this->scripting = std::make_unique<Scripting>();
}

int Engine::run() {
    scripting->test();

    return 0;
}

}