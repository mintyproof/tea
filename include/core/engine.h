#ifndef TEA_CORE_ENGINE_H
#define TEA_CORE_ENGINE_H

#include <string>
#include <vector>

#include "utils/nocopy.h"

namespace tea {

class Logger;
class Platform;
class Renderer;
class Graphics;
class Scripting;
class ScriptingEvents;

class Engine : public NoCopy {
public:
    explicit Engine(std::vector<std::string> args);
    ~Engine();

    int run();
private:
    std::vector<std::string> args;
    std::shared_ptr<Logger> logger;
    std::shared_ptr<Platform> platform;
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<Graphics> graphics;
    std::shared_ptr<Scripting> scripting;
    std::unique_ptr<ScriptingEvents> scripting_events;
};

}

#endif  // TEA_CORE_ENGINE_H
