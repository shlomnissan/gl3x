// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "example_scene.hpp"

#include <memory>

#include <gleam/lights.hpp>
#include <gleam/materials.hpp>

class ExamplePointLight : public ExampleScene {
public:
    explicit ExamplePointLight(std::shared_ptr<gleam::Camera>);

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<gleam::PhongMaterial> phong_material_;
    std::shared_ptr<gleam::PointLight> point_light_;
};