#ifndef TEA_IMPL_RENDERERGL33_H
#define TEA_IMPL_RENDERERGL33_H

#include "gfx/renderer.h"

namespace tea {

class RendererGL33 : public Renderer {
public:
    RendererGL33();

    void execute_command_buffer(const CommandBuffer& buffer) override;
};

}

#endif // TEA_IMPL_RENDERERGL33_H