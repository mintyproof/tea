#include "impl/renderergl33.h"

#include <glad/glad.h>

#include <variant>
#include "gfx/commandbuffer.h"
#include "utils/visitoverload.h"

namespace tea {

RendererGL33::RendererGL33() = default;

void RendererGL33::execute_command_buffer(const CommandBuffer& buffer) {
    // TODO: find another way of handling this- this is a hot path, recreating VisitOverload every call is non-ideal

    auto visitor = VisitOverload {
        [](const CommandSetViewport& cmd) {
            glViewport(static_cast<int>(cmd.x), static_cast<int>(cmd.y),
                       static_cast<GLsizei>(cmd.width), static_cast<GLsizei>(cmd.height));
            glDepthRange(cmd.depth_near, cmd.depth_far);
        },
        [](const CommandClearToColour& cmd) {
            glClearColor(static_cast<float>(cmd.clear_colour.get_r()),
                         static_cast<float>(cmd.clear_colour.get_g()),
                         static_cast<float>(cmd.clear_colour.get_b()),
                         static_cast<float>(cmd.clear_colour.get_a()));
            glClear(GL_COLOR_BUFFER_BIT);
        }
    };

    for (const auto& command : buffer.get_commands()) {
        std::visit(visitor, command);
    }
}

}