// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <gleam/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleFog : public ExampleScene {
public:
    explicit ExampleFog(std::shared_ptr<gleam::Camera>);

    auto ContextMenu() -> void override;
};