// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/nodes.hpp>

#include "example_scene.hpp"

class ExampleSandbox : public ExampleScene {
public:
    explicit ExampleSandbox(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;
};