// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/core.hpp>
#include <engine/math.hpp>
#include <engine/nodes.hpp>
#include <engine/resources.hpp>

#include "example_scene.hpp"

class ExampleSandbox : public ExampleScene {
public:
    explicit ExampleSandbox(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

    auto Update(float delta) -> void override;

    auto OnKeyboardEvent(engine::KeyboardEvent* event) -> void override;

private:
    engine::Frustum frustum_;

    std::shared_ptr<engine::BoundingSphere> sphere_;
    std::shared_ptr<engine::Arrow> arrow_;

    bool moving_left_ {false};
    bool moving_right_ {false};

    engine::Timer timer_ {true};
};