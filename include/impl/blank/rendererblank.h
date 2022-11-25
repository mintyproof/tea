#ifndef TEA_IMPL_BLANK_RENDERERGL33_H
#define TEA_IMPL_BLANK_RENDERERGL33_H

#include <functional>
#include <memory>

#include "gfx/renderer.h"

namespace tea {

class Platform;

// this is a blank renderer, which does not perform any genuine rendering- it simply does the bare minimum to
// pretend to be a renderer.
// as such, this renderer will not cause any visible graphics to appear on-screen.
//
// various potential uses of this:
// - porting to a new platform and attempting to get Tea compiling before implementing a renderer for it
// - placing Tea in a "headless" mode, for running projects that have no need for graphical output
// - implementing unit tests and using the blank renderer as part of functionality tests
class RendererBlank : public Renderer {
public:
    RendererBlank(std::shared_ptr<Platform> platform);
    ~RendererBlank() override;

    [[nodiscard]] const char* get_name() const override;

    void execute_command_buffer(const CommandBuffer& buffer) override;

    [[nodiscard]] int get_drawable_width() const override;
    [[nodiscard]] int get_drawable_height() const override;
    void set_vsync_enabled(bool enabled) override;
    void swap_buffers() override;
private:
    std::shared_ptr<Platform> platform;
};

}

#endif // TEA_IMPL_BLANK_RENDERERGL33_H