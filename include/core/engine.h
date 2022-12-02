#ifndef TEA_CORE_ENGINE_H
#define TEA_CORE_ENGINE_H

#include <string>
#include <vector>

#include "utils/nocopy.h"

namespace tea {

class Assets;
class Logger;
class Platform;
class Renderer;
class Graphics;
class Scripting;

struct Context {
    Assets& assets;
    Logger& logger;
    Platform& platform;
    Renderer& renderer;
    Graphics& graphics;
    Scripting& scripting;
};

class Engine : public NoCopy {
public:
    explicit Engine(std::vector<std::string> args);
    ~Engine();

    int run();

    Assets& get_assets();
    Logger& get_logger();
    Platform& get_platform();
    Renderer& get_renderer();
    Graphics& get_graphics();
    Scripting& get_scripting();
    Context get_context();
private:
    std::vector<std::string> args;
    std::shared_ptr<Assets> assets;
    std::shared_ptr<Logger> logger;
    std::shared_ptr<Platform> platform;
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<Graphics> graphics;
    std::shared_ptr<Scripting> scripting;
};

}

#endif  // TEA_CORE_ENGINE_H
