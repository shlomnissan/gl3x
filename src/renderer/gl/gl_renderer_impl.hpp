// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/core/renderer.hpp"

namespace engine {

class Renderer::Impl {
public:
    Impl(const Renderer::Parameters& params);

    auto Render(Scene* scene, Camera* camera) -> void;

private:
};

}