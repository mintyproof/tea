#ifndef TEA_CORE_ENGINE_H
#define TEA_CORE_ENGINE_H

#include <string>
#include <vector>

#include "scripting/scripting.h"
#include "utils/nocopy.h"
#include "core/platform.h"

namespace tea {

class Graphics;
class Platform;
class Renderer;
class Scripting;

class Engine : public NoCopy {
public:
    explicit Engine(std::vector<std::string> args);
    ~Engine();

    int run();
private:
    void perform_update(double delta_time);
    void perform_draw(double delta_time);

    std::vector<std::string> args;
    std::unique_ptr<Platform> platform;
    std::shared_ptr<Renderer> renderer;
    std::unique_ptr<Graphics> graphics;
    std::unique_ptr<Scripting> scripting;
};

}

#endif  // TEA_CORE_ENGINE_H
