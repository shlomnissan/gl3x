// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <algorithm>
#include <cassert>

namespace engine {

/**
 * @brief A color class representing RGBA color values.
 */
class ENGINE_EXPORT Color  {
public:
    /// @brief The red component.
    float r {1.0f};
    /// @brief The green component.
    float g {1.0f};
    /// @brief The blue component.
    float b {1.0f};
    /// @brief The alpha (transparency) component.
    float a {1.0f};

    /**
     * @brief Default constructor that initializes the color to white with full opacity.
     */
    Color() = default;

    /**
     * @brief Constructs a color with the specified red, green, and blue components.
     * The alpha component is set to 1.0 by default.
     *
     * @param r The red component of the color.
     * @param g The green component of the color.
     * @param b The blue component of the color.
     */
    Color(float r, float g, float b)
        : r(r), g(g), b(b) {}

    /**
     * @brief Constructs a color with the specified red, green, blue, and alpha components.
     *
     * @param r The red component of the color.
     * @param g The green component of the color.
     * @param b The blue component of the color.
     * @param a The alpha (transparency) component of the color.
     */
    Color(float r, float g, float b, float a)
        : r(r), g(g), b(b), a(a) {}

    /**
     * @brief Constructs a color from a hexadecimal representation.
     *
     * @param hex An unsigned integer representing the color in hexadecimal format (0xRRGGBB).
     */
    Color(unsigned int hex) :
        r(static_cast<float>(hex >> 16 & 255) / 255.f),
        g(static_cast<float>(hex >> 8 & 255) / 255.f),
        b(static_cast<float>(hex & 255) / 255.f) {}

    /**
     * @brief Provides access to the red, green, blue, or alpha component of the color.
     *
     * @param i The index of the component to access (0 for red, 1 for green, 2 for blue, 3 for alpha).
     * @return A reference to the color component.
     */
    [[nodiscard]] auto& operator[](int i) {
        assert(i >= 0 && i < 4);
        return (reinterpret_cast<float*>(this))[i];
    }

    /**
     * @brief Provides const access to the red, green, blue, or alpha component of the color.
     *
     * @param i The index of the component to access (0 for red, 1 for green, 2 for blue, 3 for alpha).
     * @return A const reference to the color component.
     */
    [[nodiscard]] const auto& operator[](int i) const {
        assert(i >= 0 && i < 4);
        return (reinterpret_cast<const float*>(this))[i];
    }

    /**
     * @brief Assigns a hexadecimal color to this Color object.
     *
     * @param hex An unsigned integer representing the color in hexadecimal format (0xRRGGBB).
     * @return A reference to this Color object.
     */
    auto operator=(unsigned int hex) -> Color& {
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
    auto operator*=(float n) -> Color& {
        r = std::clamp(r * n, 0.0f, 1.0f);
        g = std::clamp(g * n, 0.0f, 1.0f);
        b = std::clamp(b * n, 0.0f, 1.0f);
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
    [[nodiscard]] friend bool operator==(const Color& a, const Color& b) = default;

    /**
     * @brief Multiplies the color by a scalar value.
     * @related Color
     *
     * @param v The color to be scaled.
     * @param n The scalar value to multiply with.
     * @return Color A new color that is the result of scaling the original color.
     */
    [[nodiscard]] friend auto operator*(const Color& v, float n) {
        return Color {
            std::clamp(v.r * n, 0.0f, 1.0f),
            std::clamp(v.g * n, 0.0f, 1.0f),
            std::clamp(v.b * n, 0.0f, 1.0f)
        };
    }

    /**
     * @brief Multiplies a scalar value by a color.
     * @related Color
     *
     * @param n The scalar value to multiply with.
     * @param v The color to be scaled.
     * @return Color A new color that is the result of scaling the original color.
     */
    [[nodiscard]] friend auto operator*(float n, const Color& v) {
        return v * n;
    }
};

}