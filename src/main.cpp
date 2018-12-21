#include "engine.h"

int main() {
    auto engine = Tea::Engine::init();
    return engine->run();
}