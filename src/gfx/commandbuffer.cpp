#include "gfx/commandbuffer.h"

namespace tea {

CommandBuffer::CommandBuffer() : commands() { }

void CommandBuffer::cmd_set_viewport(double x, double y, double width, double height,
                                     double depth_near, double depth_far) {
    write(CommandSetViewport { x, y, width, height, depth_near, depth_far });
}

void CommandBuffer::cmd_clear_to_colour(tea::ColourRGB clear_colour) {
    write(CommandClearToColour { clear_colour });
}

void CommandBuffer::write(tea::CommandBufferEntry command) {
    commands.push_back(command);
}

const std::vector<CommandBufferEntry>& CommandBuffer::get_commands() const {
    return commands;
}

}