// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "scene/camera.hpp"

namespace engine {

class ENGINE_EXPORT CameraOrthographic : public Camera {
public:
    CameraOrthographic(
        float left = 60.0f,
        float right = 1.0f,
        float bottom = 0.1f,
        float top = 1000.0f,
        float near = 0.1f,
        float far = 100.0f
    );

private:
    float left_;
    float right_;
    float bottom_;
    float top_;

    auto UpdateProjectionTransform() -> void override;
};

}