// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleFog : public ExampleScene {
public:
    explicit ExampleFog(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

private:
    std::array<const char*, 2> fog_function_ {
        "linear", "exponential"
    };
};