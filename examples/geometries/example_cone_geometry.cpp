// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_cone_geometry.hpp"

#include "helpers.hpp"

#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleConeGeometry::ExampleConeGeometry(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 3.0f);
    Add(camera_controls);

    auto ambient = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient);

    auto directional_light = DirectionalLight::Create(0xFFFFFF, 1.0f);
    directional_light->transform.Translate({2.0f, 2.0f, 2.0f});
    Add(directional_light);
}

auto ExampleConeGeometry::ContextMenu() -> void {
    static bool dirty = false;
}