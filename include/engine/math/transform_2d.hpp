// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/matrix3.hpp"
#include "engine/math/vector2.hpp"

namespace engine {

/**
 * @brief Represents a 2D transformation.
 */
class ENGINE_EXPORT Transform2D {
public:
    // @brief The position of the transformation.
    Vector2 position {0.0f, 0.0f};

    /**
     * @brief Initializes the transformation matrix to the identity matrix.
     */
    Transform2D() = default;

    /**
     * @brief Constructs a transformation from a 3x3 matrix.
     *
     * @param m The 3x3 matrix to initialize the transformation with.
     */
    explicit Transform2D(const Matrix3& m) : transform_(m) {}

    /**
     * @brief Returns the transformation matrix.
     *
     * @return The transformation matrix representing the current scaling, translation and rotation.
     */
    [[nodiscard]] auto Get() const -> Matrix3;

private:
    /// @brief The transformation matrix, initialized to identity.
    Matrix3 transform_ {1.0f};

    /**
     * @brief Checks if two Transform objects are equal, component-wise.
     *
     * @param a The first Transform object to compare.
     * @param b The second Transform object to compare.
     * @return bool `true` if the Transform objects are equal, `false` otherwise.
     */
    [[nodiscard]] friend auto operator==(const Transform2D& a, const Transform2D& b) -> bool = default;

    /**
     * @brief Multiplies two Transform objects.
     *
     * @param a The first Transform object.
     * @param b The second Transform object.
     * @return Transform The result of multiplying the two Transform objects.
     */
    [[nodiscard]] friend auto operator*(const Transform2D& a, const Transform2D& b) {
        return Transform2D {a.Get() * b.Get()};
    }
};

}
