// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/core.hpp>
#include <engine/math.hpp>
#include <engine/nodes.hpp>

#include "example_scene.hpp"

#include <array>

class LerpAnimationDebug : public ExampleScene {
public:
    explicit LerpAnimationDebug(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

    auto Update(float delta) -> void override;

private:
    std::shared_ptr<engine::Mesh> active_point_;

    engine::Vector3 start_ {-1.5f, 0.0f, 0.0f};
    engine::Vector3 end_ {1.5f, 0.0f, 0.0f};

    float elapsed_time_ {0.0f};
};