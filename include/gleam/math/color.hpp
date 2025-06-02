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

/**
 * @brief A color class representing RGB color values.
 */
class GLEAM_EXPORT Color  {
public:
    /// @brief The red component.
    float r {1.0f};
    /// @brief The green component.
    float g {1.0f};
    /// @brief The blue component.
    float b {1.0f};

    /**
     * @brief Default constructor that initializes the color to white with full opacity.
     */
    constexpr Color() = default;

    /**
     * @brief Constructs a color with the specified red, green, and blue components.
     *
     * @param r The red component of the color.
     * @param g The green component of the color.
     * @param b The blue component of the color.
     */
    constexpr Color(float r, float g, float b)
        : r(r), g(g), b(b) {}

    /**
     * @brief Constructs a color from a hexadecimal representation.
     *
     * @param hex An unsigned integer representing the color in hexadecimal format (0xRRGGBB).
     */
    constexpr Color(unsigned int hex) :
        r(static_cast<float>(hex >> 16 & 255) / 255.f),
        g(static_cast<float>(hex >> 8 & 255) / 255.f),
        b(static_cast<float>(hex & 255) / 255.f) {}

    /**
     * @brief Constructs a color from an array of floats.
     *
     * @param color A span to an array of floats.
     */
    constexpr Color(std::span<float> color) :
        r(color[0]), g(color[1]), b(color[2]) {}

    /**
     * @brief Provides access to the red, green, or blue component of the color.
     *
     * @param i The index of the component to access (0 for red, 1 for green, 2 for blue).
     * @return A reference to the color component.
     */
    [[nodiscard]] constexpr auto& operator[](int i) {
        assert(i >= 0 && i < 3);
        switch (i) {
            case 0: return r;
            case 1: return g;
            case 2: return b;
            default: return r;
        }
    }

    /**
     * @brief Provides const access to the red, green, or blue component of the color.
     *
     * @param i The index of the component to access (0 for red, 1 for green, 2 for blue).
     * @return A const reference to the color component.
     */
    [[nodiscard]] constexpr auto& operator[](int i) const {
        assert(i >= 0 && i < 3);
        switch (i) {
            case 0: return r;
            case 1: return g;
            case 2: return b;
            default: return r;
        }
    }

    /**
     * @brief Assigns a hexadecimal color to this Color object.
     *
     * @param hex An unsigned integer representing the color in hexadecimal format (0xRRGGBB).
     * @return A reference to this Color object.
     */
    constexpr auto operator=(unsigned int hex) -> Color& {
        r = static_cast<float>(hex >> 16 & 255) / 255.f;
        g = static_cast<float>(hex >> 8 & 255) / 255.f;
        b = static_cast<float>(hex & 255) / 255.f;
        return *this;
    }

    /**
     * @brief Multiplies the color by a scalar value.
     *
     * @param n The scalar value to multiply with.
     * @return Color& A reference to the updated color.
     */
    constexpr auto operator*=(float n) -> Color& {
        r = r * n;
        g = g * n;
        b = b * n;
        return *this;
    }

private:
    /**
     * @brief Checks if two colors are equal, component-wise.
     *
     * @param a The first color to compare.
     * @param b The second color to compare.
     * @return bool `true` if the color are equal, `false` otherwise.
     */
    [[nodiscard]] friend constexpr auto operator==(const Color& a, const Color& b) -> bool = default;

    /**
     * @brief Adds two colors component-wise.
     * @related Color
     *
     * @param a The first color.
     * @param b The second color.
     * @return Color A new color that is the component-wise sum of the two colors.
     */
    [[nodiscard]] friend constexpr auto operator+(const Color& a, const Color& b) {
        return Color {a.r + b.r, a.g + b.g, a.b + b.b};
    }

    /**
     * @brief Subtracts the second Color from the first Color component-wise.
     * @related Color
     *
     * @param a The color to subtract from.
     * @param b The color to subtract.
     * @return Color A new color that is the component-wise difference of the two colors.
     */
    [[nodiscard]] friend constexpr auto operator-(const Color& a, const Color& b) {
        return Color {
            std::max(0.0f, a.r - b.r),
            std::max(0.0f, a.g - b.g),
            std::max(0.0f, a.b - b.b)
        };
    }

    /**
     * @brief Multiplies the color by a scalar value.
     * @related Color
     *
     * @param v The color to be scaled.
     * @param n The scalar value to multiply with.
     * @return Color A new color that is the result of scaling the original color.
     */
    [[nodiscard]] friend constexpr auto operator*(const Color& v, float n) {
        return Color {v.r * n, v.g * n, v.b * n};
    }

    /**
     * @brief Multiplies a scalar value by a color.
     * @related Color
     *
     * @param n The scalar value to multiply with.
     * @param v The color to be scaled.
     * @return Color A new color that is the result of scaling the original color.
     */
    [[nodiscard]] friend constexpr auto operator*(float n, const Color& v) {
        return v * n;
    }
};

/**
 * @brief Performs linear interpolation between two colors.
 * @related Color
 *
 * @param a The first color.
 * @param b The second color.
 * @param f The interpolation factor (0.0 to 1.0).
 * @return Color A new color that is the result of the linear interpolation.
 */
[[nodiscard]] constexpr auto Lerp(const Color& a, const Color& b, float f) {
    return Color {
        a.r + (b.r - a.r) * f,
        a.g + (b.g - a.g) * f,
        a.b + (b.b - a.b) * f
    };
}

}