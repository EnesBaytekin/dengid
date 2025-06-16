#pragma once

#include <tuple>
#include <algorithm>

struct Color {
    int r, g, b, a;

    Color(int red = 0, int green = 0, int blue = 0, int alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}

    void set_rgba(int red, int green, int blue, int alpha = 255) {
        r = red; g = green; b = blue; a = alpha;
    }

    void set_rgb(int red, int green, int blue) {
        r = red; g = green; b = blue;
    }

    std::tuple<int, int, int, int> get_rgba() const {
        return std::make_tuple(r, g, b, a);
    }

    std::tuple<int, int, int> get_rgb() const {
        return std::make_tuple(r, g, b);
    }

    std::tuple<float, float, float, float> get_normalized() const {
        return std::make_tuple(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }

    static int clamp(int val, int min = 0, int max = 255) {
        return std::max(min, std::min(max, val));
    }

     Color operator+(const Color& other) const {
        return Color(
            clamp(r + other.r),
            clamp(g + other.g),
            clamp(b + other.b),
            clamp(a + other.a)
        );
    }

    Color operator-(const Color& other) const {
        return Color(
            clamp(r - other.r),
            clamp(g - other.g),
            clamp(b - other.b),
            clamp(a - other.a)
        );
    }

    Color operator*(const Color& other) const {
        return Color(
            clamp((r * other.r) / 255),
            clamp((g * other.g) / 255),
            clamp((b * other.b) / 255),
            clamp((a * other.a) / 255)
        );
    }

    Color operator*(float scalar) const {
        return Color(
            clamp(static_cast<int>(r * scalar)),
            clamp(static_cast<int>(g * scalar)),
            clamp(static_cast<int>(b * scalar)),
            clamp(static_cast<int>(a * scalar))
        );
    }

    bool operator==(const Color& other) const {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }

    bool operator!=(const Color& other) const {
        return !(*this == other);
    }
};
