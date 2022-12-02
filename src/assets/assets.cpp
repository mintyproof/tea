#include "assets/assets.h"

#include <fstream>
#include <iostream>
#include <utility>

#include <cmrc/cmrc.hpp>
CMRC_DECLARE(tea);

namespace tea {

Assets::Assets() = default;
Assets::~Assets() = default;

std::optional<std::vector<uint8_t>> Assets::get_bytes(const std::string& path) noexcept {
    std::vector<uint8_t> output;

    // check embedded resources first
    auto embedded_filesystem = cmrc::tea::get_filesystem();
    if (embedded_filesystem.exists(path)) {
        auto file = embedded_filesystem.open(path);

        output.insert(output.begin(), file.begin(), file.end());
        return output;
    }

    // check filesystem next
    std::ifstream stream;
    stream.open(path, std::ifstream::in | std::ifstream::binary);
    if (stream.is_open()) {
        output.insert(output.begin(), (std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    }

    // if we've gotten this far, we haven't found it..
    return std::nullopt;
}

std::optional<std::string> Assets::get_string(const std::string& path) noexcept {
    auto bytes = get_bytes(path);
    if (bytes.has_value()) {
        return std::string(bytes->begin(), bytes->end());
    } else {
        return std::nullopt;
    }
}

}