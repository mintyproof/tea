#ifndef TEA_IMAGE_LOADER_H
#define TEA_IMAGE_LOADER_H

#include <memory>
#include <vector>

#include "image.h"

namespace Tea {
    class ImageLoader {
    public:
        /**
         * Loads a single compressed image file (eg. a PNG file)
         * @param data The compressed image file data
         * @return An owned pointer to the decompressed image instance
         */
        static std::unique_ptr<Image> load(std::vector<uint8_t>&& data);
    };
}


#endif