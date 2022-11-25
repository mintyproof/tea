#include "impl/blank/rendererblank.h"

#include <utility>

#include "core/platform.h"

namespace tea {

RendererBlank::RendererBlank(std::shared_ptr<Platform> platform) : platform(std::move(platform)) { }
RendererBlank::~RendererBlank() = default;

const char* RendererBlank::get_name() const {
    return "Blank";
}

void RendererBlank::execute_command_buffer(const CommandBuffer& buffer) {
    // ..
}

int RendererBlank::get_drawable_width() const {
    return platform->window_get_width();
}

int RendererBlank::get_drawable_height() const {
    return platform->window_get_height();
}

void RendererBlank::set_vsync_enabled(bool enabled) {
    // ..
}

void RendererBlank::swap_buffers() {
    // ..
}


}