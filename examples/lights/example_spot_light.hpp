// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "example_scene.hpp"

#include <memory>

#include <engine/lights.hpp>
#include <engine/materials.hpp>

class ExampleSpotLight : public ExampleScene {
public:
    explicit ExampleSpotLight(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<engine::PhongMaterial> phong_material_;
    std::shared_ptr<engine::SpotLight> spot_light_;
};