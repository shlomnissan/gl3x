// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/utilities.hpp"
#include "scene/camera.hpp"

#include <memory>

namespace engine {

/**
 * @brief A perspective camera class.
 *
 * This class represents a perspective camera in the scene. It extends the Camera class
 * and provides functionality specific to a perspective projection.
 */
class ENGINE_EXPORT CameraPerspective : public Camera {
public:
    /**
    * @brief Constructs a CameraPerspective object.
    *
    * Initializes a perspective camera with the specified field of view (in radians), aspect ratio,
    * and near and far clipping planes.
    *
    * @param fov The field of view in radians.
    * @param aspect The aspect ratio of the camera.
    * @param near The near clipping plane distance.
    * @param far The far clipping plane distance.
    */
    CameraPerspective(float fov, float aspect, float near, float far);

    /**
     * @brief Creates a new instance of the CameraPerspective class with default parameters.
     *
     * @param fov The field of view in degrees (default 60).
     * @param aspect The aspect ratio of the camera (width/height). Default is 1.77f (16:9).
     * @param near The near clipping plane distance. Default is 0.1f.
     * @param far The far clipping plane distance. Default is 1000.0f.
     * @return A `std::shared_ptr<CameraPerspective>` pointing to the newly created instance.
     */
    [[nodiscard]]
    static auto Create(
        float fov = 60.0f,
        float aspect = 1.77f,
        float near = 0.1f,
        float far = 1000.0f
    ) {
        return std::make_shared<CameraPerspective>(fov, aspect, near, far);
    }

private:
    /// @brief The field of view in degrees.
    float fov_;
    /// @brief The aspect ratio of the camera (width/height).
    float aspect_;

    /**
     * @brief Updates the projection matrix for the perspective camera.
     *
     * This method overrides the pure virtual function in the Camera class.
     */
    auto UpdateProjectionTransform() -> void override;
};

}