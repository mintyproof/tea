#ifndef TEA_TEXTURE_H
#define TEA_TEXTURE_H

#include <memory>

#include "../assets/image/image.h"

namespace Tea {
    /**
     * Represents a texture loaded into graphics memory, ready to be rendered.
     */
    class Texture {
    public:
        static std::shared_ptr<Texture> create(const Image& image);
        ~Texture();

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        uint32_t get_width();
        uint32_t get_height();

        unsigned int get_gl_texture();
    private:
        Texture() = default;

        unsigned int tex;
        uint32_t width;
        uint32_t height;
    };
}

#endif
