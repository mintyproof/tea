#include <SDL.h>

#include "engine.hpp"

int main()
{
    auto engine = Engine::init();
    return engine->run();
}