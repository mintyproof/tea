#include "core/engine.h"

#include "gfx/colour.h"
#include "impl/platformsdl2.h"
#include "impl/renderergl33.h"
#include "gfx/commandbuffer.h"

namespace tea {

Engine::Engine(std::vector<std::string> args) {
    this->args = std::move(args);
    this->scripting = std::make_unique<Scripting>();
}

int Engine::run() {
    scripting->test();

    PlatformSDL2 platform = PlatformSDL2();
    RendererGL33 renderer = platform.make_renderer_gl33();

    renderer.vsync_enabled(true);

    while (!platform.should_quit()) {
        platform.poll_events();

        CommandBuffer buffer;
        buffer.cmd_set_viewport(0, 0, renderer.get_drawable_width(), renderer.get_drawable_height(), 0.0, 1.0);
        buffer.cmd_clear_to_colour(ColourRGB::CORNFLOWERBLUE);
        renderer.execute_command_buffer(buffer);

        renderer.swap_buffers();
    }

    return 0;
}

}