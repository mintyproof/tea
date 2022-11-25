#include "core/engine.h"

#include <sstream>
#include <iomanip>

#include "core/platformcreator.h"
#include "gfx/colour.h"
#include "gfx/commandbuffer.h"
#include "gfx/graphics.h"
#include "gfx/renderer.h"

namespace tea {

Engine::Engine(std::vector<std::string> args) {
    this->args = std::move(args);
    auto platform_tuple = get_platform();
    this->platform = std::move(std::get<0>(platform_tuple));
    this->renderer = std::move(std::get<1>(platform_tuple));
    this->graphics = std::make_unique<Graphics>(this->renderer);
    this->scripting = std::make_unique<Scripting>();
    std::unique_ptr<Graphics> graphics = std::make_unique<Graphics>(renderer);
}

Engine::~Engine() = default;

int Engine::run() {
    scripting->test();

    renderer->vsync_enabled(true);

    double last_time = platform->runtime_seconds();
    while (!platform->should_quit()) {
        platform->poll_events();

        double now_time = platform->runtime_seconds();
        double delta_time = now_time - last_time;
        last_time = now_time;

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << (1.0 / delta_time) << " FPS";
        platform->window_set_title(oss.str());

        perform_update(delta_time);
        perform_draw(delta_time);
    }

    return 0;
}

void Engine::perform_update(double delta_time) {

}

void Engine::perform_draw(double delta_time) {
    graphics->clear_to_colour(ColourRGB::CORNFLOWERBLUE);
    renderer->swap_buffers();
}

}