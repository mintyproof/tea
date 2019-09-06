#ifndef TEA_IMAGELOADER_H
#define TEA_IMAGELOADER_H

#include <memory>
#include "image.h"

namespace Tea {
    class ImageLoader {
    public:
        static std::unique_ptr<Image> decode_image(const std::vector<uint8_t>& image_data);
    };
}

#endif