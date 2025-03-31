// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/core.hpp>
#include <engine/math.hpp>
#include <engine/nodes.hpp>

#include "example_scene.hpp"

#include <array>

class ExampleFrustumCullingTest : public ExampleScene {
public:
    explicit ExampleFrustumCullingTest(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

    auto Update(float delta) -> void override;

private:
    engine::Frustum frustum_;

    std::array<std::shared_ptr<engine::Mesh>, 2500> boxes_;
};