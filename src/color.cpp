#include "color.h"
#include <stdexcept>

Color Color::from_hex(const std::string& hex) {
    try {
        if (hex.length() == 6) {
            uint32_t color = std::stoul(hex, nullptr, 16);
            return Color::from_rgb(color);
        } else if (hex.length() == 8) {
            uint32_t color = std::stoul(hex, nullptr, 16);
            return Color::from_rgba(color);
        }
        throw std::invalid_argument("invalid hex color: input not 6 or 8 characters in length");
    } catch (const std::invalid_argument&) {
        throw std::invalid_argument("invalid hex color: input not valid hexadecimal");
    } catch (const std::out_of_range&) {
        // We're parsing to a `unsigned long` (std::stoul) which is... I think 8 bytes in length?
        // We only need 4 bytes, and anything longer is filtered out by the length check above
        // so this should never happen (unless I broke something)
        throw std::runtime_error("should never happen");
    }
}

Color Color::from_rgb(uint32_t rgb) {
    return {static_cast<uint8_t>(rgb >> 16u),
            static_cast<uint8_t>(rgb >> 8u),
            static_cast<uint8_t>(rgb),
            static_cast<uint8_t>(0xFF)};
}

Color Color::from_rgb(uint8_t r, uint8_t g, uint8_t b) {
    return {r, g, b, 0xFF};
}

Color Color::from_rgb_float(float r, float g, float b) {
    return {static_cast<uint8_t>(r * 255), static_cast<uint8_t>(g * 255), static_cast<uint8_t>(b * 255), 0xFF};
}

Color Color::from_rgba(uint32_t rgba) {
    return {static_cast<uint8_t>(rgba >> 24u),
            static_cast<uint8_t>(rgba >> 16u),
            static_cast<uint8_t>(rgba >> 8u),
            static_cast<uint8_t>(rgba)};
}

Color Color::from_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return {r, g, b, a};
}

Color Color::from_rgba_float(float r, float g, float b, float a) {
    return {static_cast<uint8_t>(r * 255),
            static_cast<uint8_t>(g * 255),
            static_cast<uint8_t>(b * 255),
            static_cast<uint8_t>(a * 255)};
}

uint32_t Color::rgba() const {
    return (static_cast<uint32_t>(r) << 24u) | (static_cast<uint32_t>(g) << 16u) | (static_cast<uint32_t>(b) << 8u) | static_cast<uint32_t>(a);
}

uint32_t Color::rgb() const {
    return (static_cast<uint32_t>(r) << 16u) | (static_cast<uint32_t>(g) << 8u) | static_cast<uint32_t>(b);
}

uint32_t Color::abgr() const {
    return (static_cast<uint32_t>(a) << 24u) | (static_cast<uint32_t>(b) << 16u) | (static_cast<uint32_t>(g) << 8u) | static_cast<uint32_t>(r);
}

Color Color::white() {
    return Color::from_rgb(255, 255, 255);
}

Color Color::black() {
    return Color::from_rgb(0, 0, 0);
}

Color Color::transparent() {
    return Color::from_rgba(0, 0, 0, 0);
}

float Color::r_float() const {
    return r / 255.f;
}

float Color::g_float() const {
    return g / 255.f;
}

float Color::b_float() const {
    return b / 255.f;
}

float Color::a_float() const {
    return a / 255.f;
}