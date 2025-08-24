/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/matrix4.hpp"
#include "gleam/math/vector3.hpp"
#include "gleam/nodes/node.hpp"

namespace gleam {

/**
 * @brief Represents available camera types.
 * @ingroup CamerasGroup
 */
enum class CameraType {
    OrthographicCamera,
    PerspectiveCamera
};

/**
 * @brief Abstract base class for camera types.
 *
 * Not intended for direct use.
 *
 * @ingroup CamerasGroup
 */
class GLEAM_EXPORT Camera : public Node {
public:
    /// @brief Projection transform.
    Matrix4 projection_transform;

    /// @brief View transform.
    Matrix4 view_transform;

    /**
     * @brief Sets the view transform to the inverse of the node's world transform.
     */
    auto SetViewTransform() -> void;

    /**
     * @brief Returns camera type.
     *
     * @return CameraType
     */
    [[nodiscard]] virtual auto GetType() const -> CameraType = 0;

    /**
     * @brief Returns node type.
     *
     * @return NodeType::CameraNode
     */
    [[nodiscard]] auto GetNodeType() const -> NodeType override {
        return NodeType::CameraNode;
    }

    /**
     * @brief Rotates the camera to face a given target position in world space.
     *
     * @param target Target world-space position to look at.
     */
    auto LookAt(const Vector3& target) -> void override;

    /**
     * @brief Returns the camera's right axis in view space.
     *
     * @return Vector3
     */
    [[nodiscard]] auto ViewRight() const {
        const auto& t = view_transform;
        return Vector3 {t[0][0], t[1][0], t[2][0]};
    }

    /**
     * @brief Returns the camera's up axis in view space.
     *
     * @return Vector3
     */
    [[nodiscard]] auto ViewUp() const {
        const auto& t = view_transform;
        return Vector3 {t[0][1], t[1][1], t[2][1]};
    }

    /**
     * @brief Returns the camera's forward axis in view space.
     *
     * @return Vector3
     */
    [[nodiscard]] auto ViewForward() const {
        const auto& t = view_transform;
        return Vector3 {t[0][2], t[1][2], t[2][2]};
    }
};

}