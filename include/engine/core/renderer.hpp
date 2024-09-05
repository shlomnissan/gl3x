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
    struct Parameters {
        int width;  ///< Width of the viewport.
        int height; ///< Height of the viewport.
    };

    Renderer(const Renderer::Parameters& params);

    auto Render(Scene* scene, Camera* camera) -> void;

    ~Renderer();

private:
    class Impl;
    std::unique_ptr<Impl> impl_ {nullptr};
};

}