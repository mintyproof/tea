#ifndef TEA_GFX_RENDERER_H
#define TEA_GFX_RENDERER_H

#include "utils/nocopy.h"

namespace tea {

class CommandBuffer;

class Renderer : public NoCopy {
public:
    virtual void execute_command_buffer(const CommandBuffer& buffer) = 0;

    // returns the width of the drawable portion of the window.
    // usually, this will not be distinct from window_get_width(), but on high-DPI displays, the size of the window
    // in screen coordinates may not match with the size of the window in pixels, making this function relevant for
    // determining the width of the window that can be drawn to.
    [[nodiscard]] virtual int get_drawable_width() const = 0;

    // returns the height of the drawable portion of the window.
    // usually, this will not be distinct from window_get_height(), but on high-DPI displays, the size of the window
    // in screen coordinates may not match with the size of the window in pixels, making this function relevant for
    // determining the height of the window that can be drawn to.
    [[nodiscard]] virtual int get_drawable_height() const = 0;

    virtual void vsync_enabled(bool enabled) = 0;
    virtual void swap_buffers() = 0;
};

}

#endif