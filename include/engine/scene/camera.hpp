// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

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
    Transform view_transform;

    /**
     * @brief Overrides the Node class function to update the world matrix.
     *
     * This function updates the underlying world matrix and copies its inverse
     * to the view transform matrix.
     */
    auto UpdateTransforms(bool update_parents = false, bool update_children = true) -> void override;

    /**
     * @brief Virtual destructor for the Camera class.
     */
    virtual ~Camera() = default;
};

}