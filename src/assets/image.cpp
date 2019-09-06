#include "image.h"

#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include <stb_image.h>
#include <fmt/core.h>

Tea::Image::Image(uint32_t width, uint32_t height, Color fill_color) : width(width), height(height) {
    this->image_data.resize(width * height * 4);
    for (size_t i = 0; i < width * height; i++) {
        this->image_data[i * 4] = fill_color.r;
        this->image_data[i * 4 + 1] = fill_color.g;
        this->image_data[i * 4 + 2] = fill_color.b;
        this->image_data[i * 4 + 3] = fill_color.a;
    }
}

Tea::Image::Image(uint32_t width, uint32_t height, std::vector<uint8_t> &&image_data)
        : width(width), height(height), image_data(std::move(image_data)) {
    if (this->image_data.size() != width * height * 4)
        throw std::runtime_error("Given parameter image_data has improper length (not w*h*4)");
}

uint32_t Tea::Image::get_width() const {
    return this->width;
}

uint32_t Tea::Image::get_height() const {
    return this->height;
}

const uint8_t &Tea::Image::get_data() const {
    return this->image_data.front();
}

void Tea::Image::fill(Color fill_color) {
    for (size_t i = 0; i < width * height; i++) {
        this->image_data[i * 4] = fill_color.r;
        this->image_data[i * 4 + 1] = fill_color.g;
        this->image_data[i * 4 + 2] = fill_color.b;
        this->image_data[i * 4 + 3] = fill_color.a;
    }
}

std::unique_ptr<Tea::Image>
Tea::Image::load(const std::string &filename, const std::vector<uint8_t> &&data) {
    int w, h, channels_in_file;

    stbi_set_flip_vertically_on_load(true);
    uint8_t* c_data = stbi_load_from_memory(&data.front(), data.size(), &w, &h, &channels_in_file, 4);
    if (c_data == nullptr) {
        // TODO: find a better method of error handling here
        throw std::runtime_error(fmt::format("Error loading image {}", filename));
    }

    std::vector<uint8_t> image_data(c_data, c_data + (w * h * 4));
    stbi_image_free(c_data);

    return std::unique_ptr<Image>(new Image(w, h, std::move(image_data)));
}
