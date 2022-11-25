#include "impl/renderergl33.h"

#include <glad/glad.h>

#include <string>
#include <utility>
#include <variant>
#include "gfx/commandbuffer.h"
#include "utils/visitoverload.h"

namespace tea {

#ifdef TEA_DEBUG
void tea_gl_post_call_callback(const char* name, void*, int, ...) {
    GLenum error_code = glad_glGetError();

    const auto error_name = [error_code]() -> const char* {
        switch (error_code) {
        case GL_NO_ERROR:                      return "GL_NO_ERROR";
        case GL_INVALID_ENUM:                  return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:                 return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:             return "GL_INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY:                 return "GL_OUT_OF_MEMORY";
        default:                               return "??";
        }
    }();

    if (error_code != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error %s in %s\n", error_name, name);
    }
}
#endif

RendererGL33::RendererGL33(RendererGL33Config config) {
    this->config = std::move(config);
    gladLoadGLLoader(this->config.func_load_proc);

#ifdef TEA_DEBUG
    glad_set_post_callback(tea_gl_post_call_callback);
#endif
}

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

int RendererGL33::get_drawable_width() const {
    return config.func_get_drawable_width();
}

int RendererGL33::get_drawable_height() const {
    return config.func_get_drawable_height();
}

void RendererGL33::vsync_enabled(bool enabled) {
    enabled ? config.func_vsync_enable()
            : config.func_vsync_disable();
}

void RendererGL33::swap_buffers() {
    config.func_swap_buffers();
}

}