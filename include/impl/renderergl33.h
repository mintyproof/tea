#ifndef TEA_IMPL_RENDERERGL33_H
#define TEA_IMPL_RENDERERGL33_H

#include <functional>
#include "gfx/renderer.h"

namespace tea {

struct RendererGL33Config {
    void* (*func_load_proc)(const char*);
    std::function<int()>  func_get_drawable_width;
    std::function<int()>  func_get_drawable_height;
    std::function<void()> func_vsync_disable;
    std::function<void()> func_vsync_enable;
    std::function<void()> func_swap_buffers;
};

class RendererGL33 : public Renderer {
public:
    explicit RendererGL33(RendererGL33Config config);
    ~RendererGL33() override;

    [[nodiscard]] const char* get_name() const override;

    void execute_command_buffer(const CommandBuffer& buffer) override;

    [[nodiscard]] int get_drawable_width() const override;
    [[nodiscard]] int get_drawable_height() const override;
    void set_vsync_enabled(bool enabled) override;
    void swap_buffers() override;
private:
    RendererGL33Config config;
};

}

#endif // TEA_IMPL_RENDERERGL33_H