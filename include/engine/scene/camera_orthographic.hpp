// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/scene/camera.hpp"

#include <memory>

namespace engine {

/**
 * @brief An orthographic camera class.
 *
 * This class represents an orthographic camera in the scene. It extends the Camera class
 * and provides functionality specific to an orthographic projection.
 */
class ENGINE_EXPORT CameraOrthographic : public Camera {
public:
    /**
     * @brief Constructs an orthographic camera object.
     *
     * @param left The left bound of the view volume.
     * @param right The right bound of the view volume.
     * @param top The top bound of the view volume.
     * @param bottom The bottom bound of the view volume.
     * @param near The distance to the near clipping plane.
     * @param far The distance to the far clipping plane.
     */
    CameraOrthographic(
        float left,
        float right,
        float top,
        float bottom,
        float near,
        float far
    );

    /**
     * @brief Creates a new instance of the CameraOrthographic class with default parameters.
     *
     * @param left The left bound of the orthographic view volume (default is -1.0f).
     * @param right The right bound of the orthographic view volume (default is 1.0f).
     * @param top The top bound of the orthographic view volume (default is 1.0f).
     * @param bottom The bottom bound of the orthographic view volume (default is -1.0f).
     * @param near The distance to the near clipping plane (default is 0.1f).
     * @param far The distance to the far clipping plane (default is 100.0f).
     * @return A `std::shared_ptr<CameraOrthographic>` pointing to the newly created instance.
     */
    [[nodiscard]]
    static auto Create(
        float left = -1.0f,
        float right = 1.0f,
        float top = 1.0f,
        float bottom = -1.0f,
        float near = 0.1f,
        float far = 100.0f
    ) {
        return std::make_shared<CameraOrthographic>(
            left, right, bottom, top, near, far
        );
    }

private:
    /// @brief The left bound of the orthographic view volume.
    float left_;
    /// @brief The right bound of the orthographic view volume.
    float right_;
    /// @brief The top bound of the orthographic view volume.
    float top_;
    /// @brief The bottom bound of the orthographic view volume.
    float bottom_;

    /**
     * @brief Updates the projection matrix for the orthographic camera.
     *
     * This method overrides the pure virtual function in the Camera class.
     */
    auto UpdateProjectionTransform() -> void override;
};

}