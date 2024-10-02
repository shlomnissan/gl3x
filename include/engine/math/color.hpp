// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

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
};

}