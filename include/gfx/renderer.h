#ifndef TEA_GFX_RENDERER_H
#define TEA_GFX_RENDERER_H

#include "utils/nocopy.h"

namespace tea {

class CommandBuffer;

class Renderer : public NoCopy {
public:
    virtual void execute_command_buffer(const CommandBuffer& buffer) = 0;
};

}

#endif