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
    /// @brief Flag indicating if the transformation matrix was modified.
    bool touched {true};

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
    [[nodiscard]] auto Get() const { return transform_; }

    /**
     * @brief Retrieves the position component of the transformation matrix.
     *
     * @return The position vector of the transformation.
     */
    [[nodiscard]] auto GetPosition() const -> Vector3;

    /**
     * @brief Sets the position component of the transformation matrix.
     *
     * @param position The position vector to set.
     */
    auto SetPosition(const Vector3& position) -> void;

    /**
     * @brief Retrieves the scale component of the transformation matrix.
     *
     * @return The scale vector of the transformation.
     */
    [[nodiscard]] auto GetScale() const -> Vector3;

    /**
     * @brief Applies a LookAt transformation.
     *
     * @param position The position of the object.
     * @param target The target position to look at.
     * @param world_up The up vector of the world.
     */
    auto LookAt(const Vector3& position, const Vector3& target, const Vector3& world_up) -> void;

    /**
     * @brief Applies a perspective transformation.
     *
     * @param fov The field of view in degrees.
     * @param aspect_ratio The aspect ratio of the view.
     * @param near The near clipping plane distance.
     * @param far The far clipping plane distance.
     */
    auto Perspective(float fov, float aspect_ratio, float near, float far) -> void;

    /**
     * @brief Applies an orthographic transformation.
     *
     * @param left The left bound of the view volume.
     * @param right The right bound of the view volume.
     * @param bottom The bottom bound of the view volume.
     * @param top The top bound of the view volume.
     * @param near The distance to the near clipping plane.
     * @param far The distance to the far clipping plane.
     */
    auto Orthographic(float left, float right, float bottom, float top, float near, float far) -> void;

private:
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