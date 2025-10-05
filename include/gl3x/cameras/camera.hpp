/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/math/frustum.hpp"
#include "gl3x/math/matrix4.hpp"
#include "gl3x/math/vector3.hpp"
#include "gl3x/nodes/node.hpp"

namespace gl3x {

/**
 * @brief Abstract base class for camera types.
 *
 * This class is not intended to be used directly. Use @ref PerspectiveCamera
 * or @ref OrthographicCamera unless you are defining your own camera type,
 * in which case it should inherit from this class.
 *
 * @ingroup CamerasGroup
 */
class GL3X_EXPORT Camera : public Node {
public:
    /// @brief Projection matrix that maps camera-space coordinates to clip space.
    Matrix4 projection_matrix {Matrix4::Identity()};

    /// @brief View matrix that maps world space to camera space.
    Matrix4 view_matrix {Matrix4::Identity()};

    /**
     * @brief Sets @ref view_matrix to the inverse of the camera's world transform.
     *
     * Called internally by the renderer before rendering a frame;
     * manual calls are rarely necessary.
     */
    auto UpdateViewMatrix() -> void;

    /**
     * @brief Updates @ref projection_matrix to reflect the current viewport size.
     *
     * Must be implemented by derived cameras to apply the appropriate projection logic.
     *
     * @param width  Viewport width in pixels.
     * @param height Viewport height in pixels.
     */
    virtual auto Resize(int width, int height) -> void = 0;

    /**
     * @brief Identifies this node as a camera.
     *
     * Always returns @ref NodeType::CameraNode, allowing runtime checks
     * to distinguish camera nodes from other node types.
     */
    [[nodiscard]] auto GetNodeType() const -> NodeType override {
        return NodeType::CameraNode;
    }

    /**
     * @brief Computes a @ref Frustum from the combined projection and view matrices.
     *
     * Useful for applying frustum culling to renderable nodes.
     */
    [[nodiscard]] auto GetFrustum() -> Frustum;

    /**
     * @brief Overrides @ref Node::LookAt to orient the camera toward a world-space target.
     *
     * Accounts for the camera’s -Z viewing direction so the camera faces the given point.
     *
     * @param target World-space position for the camera to look at.
     */
    auto LookAt(const Vector3& target) -> void override;

    /**
     * @brief Camera right axis in world space.
     */
    [[nodiscard]] auto Right() -> Vector3 {
        const auto& mat = GetWorldTransform();
        return Vector3 { mat[0][0], mat[0][1], mat[0][2] };
    }

    /**
     * @brief Camera up axis in world space.
     */
    [[nodiscard]] auto Up() -> Vector3 {
        const auto& mat = GetWorldTransform();
        return Vector3 { mat[1][0], mat[1][1], mat[1][2] };
    }

    /**
     * @brief Camera forward axis in world space.
     */
    [[nodiscard]] auto Forward() -> Vector3 {
        const auto& mat = GetWorldTransform();
        return Vector3 { -mat[2][0], -mat[2][1], -mat[2][2] };
    }
};

}