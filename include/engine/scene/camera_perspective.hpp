// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/utilities.hpp"
#include "scene/camera.hpp"

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
    * @param fov The field of view in radians. Default is 1.047197551196598f (60 degrees).
    * @param aspect The aspect ratio of the camera (width/height). Default is 1.77f (16:9).
    * @param near The near clipping plane distance. Default is 0.1f.
    * @param far The far clipping plane distance. Default is 1000.0f.
    */
    CameraPerspective(
        float fov = 1.047197551196598f, // 60 degrees
        float aspect = 1.77f, // 16:9
        float near = 0.1f,
        float far = 1000.0f
    );

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