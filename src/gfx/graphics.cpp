#include "gfx/graphics.h"

#include "gfx/colour.h"
#include "gfx/renderer.h"
#include "gfx/commandbuffer.h"

namespace tea {

Graphics::Graphics(std::shared_ptr<Renderer> renderer) : renderer(std::move(renderer)) { }

void Graphics::clear_to_colour(tea::ColourRGB colour) {
    CommandBuffer buffer;
    buffer.cmd_clear_to_colour(colour);
    renderer->execute_command_buffer(buffer);
}

}