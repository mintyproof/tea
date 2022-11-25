#ifndef TEA_GFX_COMMANDBUFFER_H
#define TEA_GFX_COMMANDBUFFER_H

#include <variant>
#include <vector>
#include "colour.h"

namespace tea {

struct CommandSetViewport {
    double x, y, width, height, depth_near, depth_far;
};

struct CommandClearToColour {
    ColourRGB clear_colour;
};

using CommandBufferEntry =
    std::variant<CommandSetViewport, CommandClearToColour>;

class CommandBuffer {
public:
    CommandBuffer();

    void cmd_set_viewport(double x, double y, double width, double height, double depth_near, double depth_far);
    void cmd_clear_to_colour(ColourRGB clear_colour);

    [[nodiscard]] const std::vector<CommandBufferEntry>& get_commands() const;
private:
    void write(CommandBufferEntry command);

    std::vector<CommandBufferEntry> commands;
};

}

#endif  // TEA_GFX_COMMANDBUFFER_H
