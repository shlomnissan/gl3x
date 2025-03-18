// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/core.hpp>
#include <engine/math.hpp>
#include <engine/nodes.hpp>
#include <engine/resources.hpp>

#include "example_scene.hpp"

#include <array>

class ExampleSandbox : public ExampleScene {
public:
    explicit ExampleSandbox(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

    auto Update(float delta) -> void override;

private:
    engine::Frustum frustum_;

    std::array<std::shared_ptr<engine::Mesh>, 2500> boxes_;
};