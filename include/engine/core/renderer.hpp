// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/scene/scene.hpp"
#include "engine/scene/camera.hpp"

#include <memory>

namespace engine {

class ENGINE_EXPORT Renderer {
public:
    auto Render(
        std::shared_ptr<Scene>& scene,
        std::shared_ptr<Camera>& camera
    ) -> void;

private:
    class Impl;
    std::unique_ptr<Impl> impl_ {nullptr};
};

}