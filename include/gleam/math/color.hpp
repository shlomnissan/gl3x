/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include <algorithm>
#include <cassert>
#include <span>

namespace gleam {

class GLEAM_EXPORT Color  {
public:
    float r {1.0f};
    float g {1.0f};
    float b {1.0f};

    constexpr Color() = default;

    constexpr Color(float r, float g, float b) : r(r), g(g), b(b) {}

    constexpr Color(unsigned int hex) :
        r(static_cast<float>(hex >> 16 & 255) / 255.f),
        g(static_cast<float>(hex >> 8 & 255) / 255.f),
        b(static_cast<float>(hex & 255) / 255.f) {}

    constexpr Color(std::span<float> color) : r(color[0]), g(color[1]), b(color[2]) {}

    [[nodiscard]] constexpr auto& operator[](int i) {
        assert(i >= 0 && i < 3);
        switch (i) {
            case 0: return r;
            case 1: return g;
            case 2: return b;
            default: return r;
        }
    }

    [[nodiscard]] constexpr auto& operator[](int i) const {
        assert(i >= 0 && i < 3);
        switch (i) {
            case 0: return r;
            case 1: return g;
            case 2: return b;
            default: return r;
        }
    }

    constexpr auto operator=(unsigned int hex) -> Color& {
        r = static_cast<float>(hex >> 16 & 255) / 255.f;
        g = static_cast<float>(hex >> 8 & 255) / 255.f;
        b = static_cast<float>(hex & 255) / 255.f;
        return *this;
    }

    constexpr auto operator*=(float n) -> Color& {
        r = r * n;
        g = g * n;
        b = b * n;
        return *this;
    }

private:
    [[nodiscard]] friend constexpr auto operator==(const Color& a, const Color& b) -> bool = default;

    [[nodiscard]] friend constexpr auto operator+(const Color& a, const Color& b) {
        return Color {a.r + b.r, a.g + b.g, a.b + b.b};
    }

    [[nodiscard]] friend constexpr auto operator-(const Color& a, const Color& b) {
        return Color {
            std::max(0.0f, a.r - b.r),
            std::max(0.0f, a.g - b.g),
            std::max(0.0f, a.b - b.b)
        };
    }

    [[nodiscard]] friend constexpr auto operator*(const Color& v, float n) {
        return Color {v.r * n, v.g * n, v.b * n};
    }

    [[nodiscard]] friend constexpr auto operator*(float n, const Color& v) {
        return v * n;
    }
};

[[nodiscard]] constexpr auto Lerp(const Color& a, const Color& b, float f) {
    return Color {
        a.r + (b.r - a.r) * f,
        a.g + (b.g - a.g) * f,
        a.b + (b.b - a.b) * f
    };
}

}