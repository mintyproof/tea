#include "core/engine.h"

#include <sstream>
#include <iomanip>

#include "core/logger.h"
#include "core/platform.h"
#include "gfx/renderer.h"
#include "gfx/graphics.h"
#include "scripting/bindings.h"
#include "scripting/scripting.h"
#include "core/platformcreator.h"
#include "gfx/colour.h"
#include "gfx/commandbuffer.h"

namespace tea {

Engine::Engine(std::vector<std::string> args) {
    this->args = std::move(args);
    this->logger = std::make_shared<Logger>();
    auto platform_tuple = create_platform();
    this->platform = std::move(std::get<0>(platform_tuple));
    this->renderer = std::move(std::get<1>(platform_tuple));
    this->graphics = std::make_shared<Graphics>(this->renderer);
    this->scripting = std::make_shared<Scripting>(this);
    generate_bindings(*this->scripting);

    this->renderer->set_vsync_enabled(true); // enable vsync by default

#ifndef TEA_DEBUG
    // if we're not in debug mode, let's not log from C++; only Wren code should log
    this->logger->set_cpp_logging_allowed(false);
#endif
    LOG(this->logger, Info, "starting..");
}

Engine::~Engine() = default;

int Engine::run() {
    double last_time = platform->runtime_seconds();
    while (!platform->should_quit()) {
        platform->poll_events();

        double now_time = platform->runtime_seconds();
        double delta_time = now_time - last_time;
        last_time = now_time;

        std::ostringstream oss;
        oss << "Tea Debug [" << platform->get_name() << "] ["
            << renderer->get_name() << "] ("
            << std::fixed << std::setprecision(1) << (1.0 / delta_time) << " FPS)";
        platform->window_set_title(oss.str());

        scripting->on_update(delta_time);

        graphics->clear_to_colour(ColourRGB::CORNFLOWERBLUE);
        scripting->on_draw(delta_time);
        renderer->swap_buffers();
    }

    scripting->on_quit();

    LOG(this->logger, Info, "quitting..");

    return 0;
}

Assets& Engine::get_assets() {
    return *this->assets;
}

Logger& Engine::get_logger() {
    return *this->logger;
}

Platform& Engine::get_platform() {
    return *this->platform;
}

Renderer& Engine::get_renderer() {
    return *this->renderer;
}

Graphics& Engine::get_graphics() {
    return *this->graphics;
}

Scripting& Engine::get_scripting() {
    return *this->scripting;
}

Context Engine::get_context() {
    return {
        *this->assets,
        *this->logger,
        *this->platform,
        *this->renderer,
        *this->graphics,
        *this->scripting
    };
}

}