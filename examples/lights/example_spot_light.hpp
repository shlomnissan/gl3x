// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleSpotLight : public ExampleScene {
public:
    explicit ExampleSpotLight(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<engine::Mesh> mesh_;
};