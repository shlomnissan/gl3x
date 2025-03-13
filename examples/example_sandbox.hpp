// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/core.hpp>
#include <engine/nodes.hpp>
#include <engine/resources.hpp>

#include "example_scene.hpp"

class ExampleSandbox : public ExampleScene {
public:
    explicit ExampleSandbox(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<engine::BoundingSphere> sphere_;
    std::shared_ptr<engine::Arrow> arrow_;

    engine::Timer timer_ {true};
};