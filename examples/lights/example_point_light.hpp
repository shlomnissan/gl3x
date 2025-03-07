// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "example_scene.hpp"

#include <memory>

#include <engine/lights.hpp>

class ExamplePointLight : public ExampleScene {
public:
    explicit ExamplePointLight(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<engine::PointLight> point_light_;
};