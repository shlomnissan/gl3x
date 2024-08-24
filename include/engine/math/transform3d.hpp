// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/matrix4.hpp"
#include "engine/math/vector3.hpp"

namespace engine {

/**
 * @brief Represents a 3D transformation.
 */
class ENGINE_EXPORT Transform3D {
public:
    /**
     * @brief Applies a uniform scaling transformation.
     *
     * @param value The scaling factor to apply.
     *
     */
    auto Scale(float value) -> void;

    /**
     * @brief Applies a translation transformation.
     *
     * @param axis The direction in which to translate.
     * @param distance The distance to translate along the specified axis.
     */
    auto Translate(const Vector3& axis, float distance) -> void;

    /**
     * @brief Computes the current transformation matrix.
     *
     * This method calculates and returns the transformation matrix, If the transformation
     * is marked as dirty, it will be recalculated before being returned.
     *
     * @return The transformation matrix representing the current scaling and translation.
     */
    [[nodiscard]] auto ToMatrix() -> Matrix4;

    /**
     * @brief Checks if the transformation matrix is dirty.
     *
     * @return True if the transformation matrix needs to be recalculated, false otherwise.
     */
    auto IsDirty() const { return is_dirty_; }

private:
    /// @brief Flag indicating if the transformation matrix needs to be recalculated.
    bool is_dirty_ {true};

    /// @brief The transformation matrix, initialized to identity.
    Matrix4 transform_ {1.0f};

    /// @brief The position vector representing translation.
    Vector3 position_ {0.0f};

    /// @brief The scale vector representing scaling.
    Vector3 scale_ {1.0f};
};

}