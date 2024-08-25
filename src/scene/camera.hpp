// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/matrix4.hpp"
#include "engine/scene/node.hpp"

namespace engine {

/**
 * @brief Represents a camera in the scene.
 */
class Camera : public Node {
public:
    /**
     * @brief Retrieves the projection matrix of the camera.
     * 
     * @return The projection matrix as a Matrix4 object.
     */
    auto GetProjectionMatrix() const { return projection_transform_; }

    /**
     * @brief Retrieves the view matrix of the camera.
     * 
     * @return The view matrix as a Matrix4 object.
     */
    auto GetViewMatrix() const { return view_transform_; }

    /**
     * @brief Overrides the Node class function to update the world matrix.
     *
     * This function updates the underlying world matrix and copies its inverse 
     * to the view transform matrix.
     */
    auto UpdateTransforms() -> void override;

    /**
     * @brief Virtual destructor for the Camera class.
     */
    virtual ~Camera() = default;

protected:
    /// @brief The near clipping plane distance.
    float near_;
    /// @brief The far clipping plane distance.
    float far_;
    /// @brief The projection matrix of the camera.
    Matrix4 projection_transform_;
    /// @brief The inverse of the world transform attached to the node.
    Matrix4 view_transform_;

    /**
     * @brief Updates the projection transform.
     * 
     * This pure virtual function must be implemented by derived classes to
     * update the projection matrix based on camera parameters.
     */
    virtual auto UpdateProjectionTransform() -> void = 0;
};

}