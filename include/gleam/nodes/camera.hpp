/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/math/matrix4.hpp"
#include "gleam/nodes/node.hpp"

namespace gleam {

/**
 * @brief An abstract base class for cameras.
 */
class Camera : public Node {
public:
    /// @brief The projection matrix of the camera.
    Matrix4 projection_transform;

    /// @brief The view matrix of the camera.
    Matrix4 view_transform;

    /**
     * @brief Updates the view matrix of the camera by the
     * inverse of the world transformation.
     */
    auto UpdateViewTransform() -> void;

    /**
     * @brief Returns node type.
     *
     * @return NodeType::CameraNode
     */
    [[nodiscard]] auto GetNodeType() const -> NodeType override {
        return NodeType::CameraNode;
    }

private:
    /**
     * @brief Sets the projection matrix of the camera.
     */
    virtual auto SetProjection() -> void = 0;
};

}