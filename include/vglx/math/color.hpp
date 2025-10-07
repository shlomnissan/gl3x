/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx_export.h"

#include <algorithm>
#include <cassert>
#include <span>

namespace vglx {

/**
 * @brief Represents an RGB color with floating-point components.
 *
 * @ingroup MathGroup
 */
class VGLX_EXPORT Color  {
public:
    float r {1.0f}; ///< Red channel [0.0, 1.0].
    float g {1.0f}; ///< Green channel [0.0, 1.0].
    float b {1.0f}; ///< Blue channel [0.0, 1.0].

    /**
     * @brief Constructs a Color object.
     */
    constexpr Color() = default;

    /**
     * @brief Constructs a Color object from individual RGB components.
     *
     * @param r Red component.
     * @param g Green component.
     * @param b Blue component.
     */
    constexpr Color(float r, float g, float b) : r(r), g(g), b(b) {}

    /**
     * @brief Constructs a Color object from a hexadecimal value.
     *
     * The hex format is 0xRRGGBB. Each channel is normalized to [0.0, 1.0].
     *
     * @param hex Hexadecimal color code.
     */
    constexpr Color(unsigned int hex) :
        r(static_cast<float>(hex >> 16 & 255) / 255.f),
        g(static_cast<float>(hex >> 8 & 255) / 255.f),
        b(static_cast<float>(hex & 255) / 255.f) {}

    /**
     * @brief Constructs a Color object from a span of 3 float values.
     *
     * @param color Span containing red, green, and blue components.
     */
    constexpr Color(std::span<float> color) : r(color[0]), g(color[1]), b(color[2]) {}

    /**
     * @brief Accesses color components by index.
     *
     * @param i Index (0 for r, 1 for g, 2 for b).
     * @return Reference to the component.
     */
    [[nodiscard]] constexpr auto& operator[](int i) {
        assert(i >= 0 && i < 3);
        switch (i) {
            case 0: return r;
            case 1: return g;
            case 2: return b;
            default: return r; // placeholder
        }
    }

    /**
     * @brief Accesses color components by index (const).
     *
     * @param i Index (0 for r, 1 for g, 2 for b).
     * @return Const reference to the component.
     */
    [[nodiscard]] constexpr auto& operator[](int i) const {
        assert(i >= 0 && i < 3);
        switch (i) {
            case 0: return r;
            case 1: return g;
            case 2: return b;
            default: return r; // placeholder
        }
    }

    /**
     * @brief Assigns a new color from a hexadecimal value.
     *
     * @param hex Hexadecimal color code in 0xRRGGBB format.
     * @return Reference to this color.
     */
    constexpr auto operator=(unsigned int hex) -> Color& {
        r = static_cast<float>(hex >> 16 & 255) / 255.f;
        g = static_cast<float>(hex >> 8 & 255) / 255.f;
        b = static_cast<float>(hex & 255) / 255.f;
        return *this;
    }

    /**
     * @brief Multiplies the color by a scalar in-place.
     *
     * @param n Scalar value.
     * @return Reference to this color.
     */
    constexpr auto operator*=(float n) -> Color& {
        r = r * n;
        g = g * n;
        b = b * n;
        return *this;
    }

private:
    /// @brief Equality comparison operator.
    [[nodiscard]] friend constexpr auto operator==(const Color& a, const Color& b) -> bool = default;

    /// @brief Adds two colors component-wise.
    [[nodiscard]] friend constexpr auto operator+(const Color& a, const Color& b) {
        return Color {a.r + b.r, a.g + b.g, a.b + b.b};
    }

    /// @brief Subtracts one color from another, clamped at 0.
    [[nodiscard]] friend constexpr auto operator-(const Color& a, const Color& b) {
        return Color {
            std::max(0.0f, a.r - b.r),
            std::max(0.0f, a.g - b.g),
            std::max(0.0f, a.b - b.b)
        };
    }

    /// @brief Scalar multiplication (color * scalar).
    [[nodiscard]] friend constexpr auto operator*(const Color& v, float n) {
        return Color {v.r * n, v.g * n, v.b * n};
    }

    /// @brief Scalar multiplication (scalar * color).
    [[nodiscard]] friend constexpr auto operator*(float n, const Color& v) {
        return v * n;
    }
};

/**
 * @brief Linearly interpolates between two vectors.
 * @relatesalso Color
 *
 * @param a Start color.
 * @param b End color.
 * @param f Interpolation factor [0, 1].
 * @return Interpolated color.
 */
[[nodiscard]] constexpr auto Lerp(const Color& a, const Color& b, float f) {
    return Color {
        a.r + (b.r - a.r) * f,
        a.g + (b.g - a.g) * f,
        a.b + (b.b - a.b) * f
    };
}

}