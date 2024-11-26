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
class ENGINE_EXPORT Transform {
public:
    /**
     * @brief Default constructor that initializes the transformation matrix to the identity matrix.
     */
    Transform() = default;

    /**
     * @brief Constructs a transformation from a 4x4 matrix.
     *
     * @param m The 4x4 matrix to initialize the transformation with.
     */
    explicit Transform(const Matrix4& m) : transform_(m) {}

    /**
     * @brief Applies a uniform scaling transformation.
     *
     * @param value The scaling factor to apply.
     */
    auto Scale(float value) -> void;

    /**
     * @brief Applies a scaling transformation.
     *
     * @param value The scaling vector to apply.
     */
    auto Scale(const Vector3& value) -> void;

    /**
     * @brief Applies a rotation transformation around a specified axis.
     *
     * @param axis The axis to rotate around. Must be (1,0,0), (0,1,0), or (0,0,1).
     * @param angle The angle to rotate by, in radians.
     */
    auto Rotate(const Vector3& axis, float angle) -> void;

    /**
     * @brief Applies a translation transformation.
     *
     * @param value The translation vector to apply.
     */
    auto Translate(const Vector3& value) -> void;

    /**
     * @brief Returns the transformation matrix.
     *
     *
     * @return The transformation matrix representing the current scaling, translation and rotation.
     */
    [[nodiscard]] auto Get() -> Matrix4;

    /**
     * @brief Checks if the transformation matrix is dirty.
     *
     * @return True if the transformation matrix needs to be recalculated, false otherwise.
     */
    [[nodiscard]] auto IsDirty() const { return is_dirty_; }

    /**
     * @brief Retrieves the position component of the transformation matrix.
     *
     * @return The position vector of the transformation.
     */
    [[nodiscard]] auto GetPosition() const -> Vector3;

    /**
     * @brief Retrieves the scale component of the transformation matrix.
     *
     * @return The scale vector of the transformation.
     */
    [[nodiscard]] auto GetScale() const -> Vector3;

private:
    /// @brief Flag indicating if the transformation matrix needs to be recalculated.
    bool is_dirty_ {true};

    /// @brief The transformation matrix, initialized to identity.
    Matrix4 transform_ {1.0f};

   /**
     * @brief Checks if two Transform objects are equal, component-wise.
     *
     * @param a The first Transform object to compare.
     * @param b The second Transform object to compare.
     * @return bool `true` if the Transform objects are equal, `false` otherwise.
     */
    [[nodiscard]] friend auto operator==(const Transform& a, const Transform& b) -> bool = default;

    /**
     * @brief Multiplies two Transform objects.
     *
     * @param a The first Transform object.
     * @param b The second Transform object.
     * @return Transform The result of multiplying the two Transform objects.
     */
    [[nodiscard]] friend auto operator*(const Transform& a, const Transform& b) -> Transform {
        return Transform {a.transform_ * b.transform_};
    }
};

}