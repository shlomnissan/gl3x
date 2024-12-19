// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/transform_2d.hpp"

#include "core/disposable.hpp"
#include "core/identity.hpp"

namespace engine {

/**
 * @brief Texutre base class.
 */
class Texture : public Disposable, public Identity {
public:
    /// @brief The UV transformation matrix.
    Transform2D transform;

    /**
     * @brief Set the offset of the texture on the X-axis.
     */
    auto OffsetX(float value) { transform.Translate({value, 0.0f}); }

    /**
     * @brief Set the offset of the texture on the Y-axis.
     */
    auto OffsetY(float value) { transform.Translate({0.0f, value}); }

    /**
     * @brief Set the uniform scale of the texture.
     */
    auto Scale(float value) { transform.Scale({value, value}); }

    /**
     * @brief Set the rotation angle of the texture.
     */
    auto Rotate(float angle) { transform.Rotate(angle); }

    /**
     * @brief Set the center of UV transformation.
     */
    auto SetCenter(float x, float y) { transform.SetCenter({x, y}); }
};

}