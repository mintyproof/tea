#ifndef TEA_VEC_H
#define TEA_VEC_H

#include <cmath>

namespace Tea {
    struct Vec2 {
        Vec2(): x(0), y(0) {}
        Vec2(float x, float y): x(x), y(y) {}

        inline Vec2 operator+(Vec2 other) {
            return Vec2(x + other.x, y + other.y);
        }

        inline Vec2 operator-(Vec2 other) {
            return Vec2(x - other.x, y - other.y);
        }

        inline Vec2 operator*(Vec2 other) {
            return Vec2(x * other.x, y * other.y);
        }

        inline Vec2 operator*(float other) {
            return Vec2(x * other, y * other);
        }

        inline Vec2 operator/(Vec2 other) {
            return Vec2(x / other.x, y / other.y);
        }

        inline Vec2 operator/(float other) {
            return Vec2(x / other, y / other);
        }

        inline float len() {
            return std::sqrt(len2());
        }

        inline float len2() {
            return x*x + y*y;
        }

        Vec2 nor() {
            if (x == 0 && y == 0) return Vec2(0, 0);
            return *this / len();
        }

        float x;
        float y;
    };
}

#endif