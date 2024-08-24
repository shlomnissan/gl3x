// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "scene/camera.hpp"

namespace engine {

class ENGINE_EXPORT CameraPerspective : public Camera {
public:
    CameraPerspective(float fov = 60.0f, float aspect = 1.0f, float near = 0.1f, float far = 1000.0f);
    
    auto updateProjectionTransform() -> void override;

private:
    float fov_;
    float aspect_;
    float near_;
    float far_;
};

}