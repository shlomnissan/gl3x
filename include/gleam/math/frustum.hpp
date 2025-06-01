// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"

#include "gleam/math/box3.hpp"
#include "gleam/math/matrix4.hpp"
#include "gleam/math/sphere.hpp"
#include "gleam/math/plane.hpp"

#include <array>

namespace gleam {

/**
 * @brief Represents a frustum in 3D space.
 */
struct GLEAM_EXPORT Frustum {
    /// @brief The six planes that make up the frustum.
    std::array<Plane, 6> planes = {};

    /**
     * @brief Default constructor for the Frustum class.
     */
    Frustum() = default;

    /**
     * @brief Constructs a new Frustum object using a view and projection matrix.
     */
    explicit Frustum(const Matrix4& projection);

    /**
     * @brief Reset the Frustum object planes using a view and projection matrix.
     */
    auto SetWithViewProjection(const Matrix4& projection) -> void;

    /**
     * @brief Determines if the frustum contains a point.
     *
     * @param point The point to check for containment.
     * @return True if the frustum contains the point, false otherwise.
     */
    [[nodiscard]] auto ContainsPoint(const Vector3& point) const -> bool;

    /**
     * @brief Determines if the frustum intersects with an axis-aligned bounding box.
     *
     * @param box The box to check for intersection.
     * @return True if the frustum intersects with the box, false otherwise.
     */
    [[nodiscard]] auto IntersectsWithBox3(const Box3& box) const -> bool;

    /**
     * @brief Determines if the frustum intersects with a sphere.
     *
     * @param sphere The sphere to check for intersection.
     * @return True if the frustum intersects with the sphere, false otherwise.
     */
    [[nodiscard]] auto IntersectsWithSphere(const Sphere& sphere) const -> bool;
};

}