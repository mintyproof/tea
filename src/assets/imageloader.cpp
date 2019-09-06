#include <iostream>
#include "imageloader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::unique_ptr<Tea::Image> Tea::ImageLoader::decode_image(const std::vector<uint8_t> &image_data) {
    int w, h, channels_in_file;

    stbi_set_flip_vertically_on_load(true);
    uint8_t* c_data = stbi_load_from_memory(&image_data.front(), image_data.size(), &w, &h, &channels_in_file, 4);
    if (c_data == nullptr) {
        // TODO: find a better method of error handling here
        std::cerr << "Error loading image." << std::endl;
    }

    std::vector<uint8_t> data(c_data, c_data + (w * h * 4));
    stbi_image_free(c_data);

    return std::unique_ptr<Image>(new Image(w, h, std::move(data)));
}
