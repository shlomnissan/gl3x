// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"
#include "gleam/math/matrix3.hpp"
#include "gleam/math/vector2.hpp"

namespace engine {

/**
 * @brief Represents a 2D transformation.
 */
class GLEAM_EXPORT Transform2 {
public:
    /**
     * @brief Update the position of the transformation.
     *
     * @param value The translation vector to apply.
     */
    auto Translate(const Vector2& value) -> void;

    /**
     * @brief Update the scale of the transformation.
     *
     * @param value The scaling vector to apply.
     */
    auto Scale(const Vector2& value) -> void;

    /**
     * @brief Update the rotation of the transformation.
     *
     * @param angle The angle to rotate by, in radians.
     */
    auto Rotate(float angle) -> void;

    /**
     * @brief Sets the position of the transformation.
     *
     * @param position The position vector to set.
     */
    auto SetPosition(const Vector2& position) -> void;

    /**
     * @brief Sets the scale of the transformation.
     *
     * @param scale The scale vector to set.
     */
    auto SetScale(const Vector2& scale) -> void;

    /**
     * @brief Sets the rotation of the transformation.
     *
     * @param rotation The rotation angle to set.
     */
    auto SetRotation(float rotation) -> void;

    /**
     * @brief Sets the center of the transformation.
     *
     * @param center The center vector to set.
     */
    auto SetCenter(const Vector2& center) -> void;

    /**
     * @brief Retrieves the position component of the transformation matrix.
     *
     * @return The position vector of the transformation.
     */
    [[nodiscard]] auto GetPosition() const { return position_; }

    /**
     * @brief Retrieves the scale component of the transformation matrix.
     *
     * @return The scale vector of the transformation.
     */
    [[nodiscard]] auto GetScale() const { return scale_; }

    /**
     * @brief Retrieves the rotation component of the transformation matrix.
     *
     * @return The rotation angle of the transformation.
     */
    [[nodiscard]] auto GetRotation() const { return rotation_; }

    /**
     * @brief Retrieves the center component of the transformation matrix.
     *
     * @return The center vector of the transformation.
     */
    [[nodiscard]] auto GetCenter() const { return center_; }

    /**
     * @brief Returns the transformation matrix.
     *
     * @return The transformation matrix representing the current scaling, translation and rotation.
     */
    [[nodiscard]] auto Get() -> Matrix3;

private:
    /// @brief The transformation matrix, initialized to identity.
    Matrix3 transform_ {1.0f};

    /// @brief The position of the transformation.
    Vector2 position_ {0.0f, 0.0f};

    /// @brief The scale of the transformation.
    Vector2 scale_ {1.0f, 1.0f};

    /// @brief The center of the transformation.
    Vector2 center_ {0.0f, 0.0f};

    /// @brief The rotation of the transformation.
    float rotation_ {0.0f};

    /// @brief Flag indicating if the matrix should be recalculated.
    bool touched_ {true};
};

}
