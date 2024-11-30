// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/matrix4.hpp"
#include "engine/math/transform.hpp"
#include "engine/scene/node.hpp"

namespace engine {

/**
 * @brief Represents a camera in the scene.
 */
class Camera : public Node {
public:
    /// @brief The projection matrix of the camera.
    Transform projection_transform;

    /// @brief The inverse of the world transform attached to the node.
    Matrix4 view_transform;

    /**
     * @brief Updates the view transformation matrix of the camera.
     */
    auto UpdateViewTransform() -> void;

    /**
     * @brief Virtual destructor for the Camera class.
     */
    virtual ~Camera() = default;
};

}