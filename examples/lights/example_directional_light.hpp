// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "example_scene.hpp"

#include <memory>

#include <engine/lights.hpp>
#include <engine/materials.hpp>

class ExampleDirectionalLight : public ExampleScene {
public:
    explicit ExampleDirectionalLight(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<engine::DirectionalLight> directional_light_;
    std::shared_ptr<engine::PhongMaterial> phong_material_;
};