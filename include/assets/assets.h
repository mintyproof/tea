#ifndef TEA_ASSETS_ASSETS_H
#define TEA_ASSETS_ASSETS_H

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace tea {

class Assets {
public:
    Assets();
    ~Assets();

    [[nodiscard]] std::optional<std::vector<uint8_t>> get_bytes(const std::string& path) noexcept;
    [[nodiscard]] std::optional<std::string> get_string(const std::string& path) noexcept;
};

}

#endif