// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleDirectionalLight : public ExampleScene {
public:
    explicit ExampleDirectionalLight(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;
};