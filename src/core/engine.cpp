#include "core/engine.h"

#include <sstream>
#include <iomanip>

#include "core/logger.h"
#include "core/platform.h"
#include "gfx/renderer.h"
#include "gfx/graphics.h"
#include "scripting/scripting.h"
#include "scripting/scriptingevents.h"

#include "core/platformcreator.h"
#include "gfx/colour.h"
#include "gfx/commandbuffer.h"

namespace tea {

Engine::Engine(std::vector<std::string> args) {
    this->args = std::move(args);
    this->logger = std::make_shared<Logger>();
    auto platform_tuple = get_platform();
    this->platform = std::move(std::get<0>(platform_tuple));
    this->renderer = std::move(std::get<1>(platform_tuple));
    this->graphics = std::make_shared<Graphics>(this->renderer);
    this->scripting = std::make_shared<Scripting>(this);
    //this->scripting_events = this->scripting->get_scripting_events();

#ifndef TEA_DEBUG
    // if we're not in debug mode, let's not log from C++- only Wren code should log
    this->logger->set_cpp_logging_allowed(false);
#endif

    this->renderer->set_vsync_enabled(true); // enable vsync by default

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

        //scripting_events->on_update(delta_time);

        graphics->clear_to_colour(ColourRGB::CORNFLOWERBLUE);
        //scripting_events->on_draw(delta_time);
        renderer->swap_buffers();
    }

    //scripting_events->on_quit();

    LOG(this->logger, Info, "quitting..");

    return 0;
}

}