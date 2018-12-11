#include "engine.h"

#undef main
int main() {
    auto engine = Tea::Engine::init();
    return engine->run();
}