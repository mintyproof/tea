#ifndef TEA_IMAGE_H
#define TEA_IMAGE_H

#include <cstdint>
#include <vector>

#include "../color.h"
#include "asset.h"

namespace Tea {
    /**
     * Represents an image loaded into memory in uncompressed RGBA8888 form.
     */
    class Image: public Asset {
    public:
        Image(uint32_t width, uint32_t height, Color fill_color);
        Image(uint32_t width, uint32_t height, std::vector<uint8_t>&& image_data);
        static std::unique_ptr<Image> load(const std::string &filename, const std::vector<uint8_t> &&data);

        uint32_t get_width() const;
        uint32_t get_height() const;

        const uint8_t& get_data() const;

        void fill(Color fill_color);
    private:
        uint32_t width;
        uint32_t height;
        std::vector<uint8_t> image_data;
    };
}


#endif