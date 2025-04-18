// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_model_geometry.hpp"

#include "ui_helpers.hpp"

#include <engine/lights.hpp>
#include <engine/resources.hpp>

using namespace engine;
using namespace engine::math;

ExampleModelGeometry::ExampleModelGeometry(std::shared_ptr<engine::Camera> camera) {
    show_context_menu_ = false;

    Add(CameraOrbit::Create(camera, 3.0f, DegToRad(15.0f), DegToRad(45.0f)));
    Add(AmbientLight::Create(0xFFFFFF, 0.3f));

    auto point_light = PointLight::Create(0xFFFFFF, 1.0f);
    point_light->transform.Translate({2.0f, 2.0f, -2.0f});
    point_light->SetDebugMode(true);
    Add(point_light);
}

auto ExampleModelGeometry::OnAttached() -> void {
    // TODO: Implement
}

auto ExampleModelGeometry::ContextMenu() -> void {
    // Empty
}