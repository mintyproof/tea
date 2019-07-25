#ifndef TEA_COLOR_H
#define TEA_COLOR_H

#include <cstdint>
#include <string>

struct Color {
    static Color from_hex(const std::string& hex);  // Throws std::invalid_argument
    static Color from_rgb(uint32_t rgb); // 0x__RRGGBB
    static Color from_rgb(uint8_t r, uint8_t g, uint8_t b);
    static Color from_rgb_float(float r, float g, float b); // Internally converts to 8bpc
    static Color from_rgba(uint32_t rgba); // 0xRRGGBBAA
    static Color from_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    static Color from_rgba_float(float r, float g, float b, float a); // Internally converts to 8bpc

    static Color white();
    static Color black();
    static Color transparent();

    float r_float() const;
    float g_float() const;
    float b_float() const;
    float a_float() const;

    uint32_t rgb() const;
    uint32_t rgba() const;
    uint32_t abgr() const;

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

#endif  // TEA_COLOR_H
