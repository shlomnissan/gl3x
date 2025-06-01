// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <gleam/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleArrowResource : public ExampleScene {
public:
    explicit ExampleArrowResource(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;
};