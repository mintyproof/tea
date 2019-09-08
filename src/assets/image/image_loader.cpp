#include "image_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include <fmt/core.h>
#include <stb_image.h>

std::unique_ptr<Tea::Image> Tea::ImageLoader::load(std::vector<uint8_t> &&data) {
    int w, h, channels_in_file;

    stbi_set_flip_vertically_on_load(true);
    uint8_t* c_data = stbi_load_from_memory(&data.front(), data.size(), &w, &h, &channels_in_file, 4);
    if (c_data == nullptr) {
        // TODO: find a better method of error handling here
        throw std::runtime_error(fmt::format("Error loading image"));
    }

    std::vector<uint8_t> image_data(c_data, c_data + (w * h * 4));
    stbi_image_free(c_data);

    return std::unique_ptr<Image>(new Image(w, h, std::move(image_data)));
}
