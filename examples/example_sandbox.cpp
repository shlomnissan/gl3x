// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_sandbox.hpp"

#include <engine/geometries.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleSandbox::ExampleSandbox(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 5.0f);
    Add(camera_controls);

    const auto geometry = SphereGeometry::Create({.radius = 1.0f});
    const auto material = FlatMaterial::Create();
    material->color = 0x049EF4;

    auto mesh = Mesh::Create(geometry, material);
    mesh->CreateBoundingBox();
    Add(mesh);

    if (mesh->bounding_box.has_value()) {
        Add(BoundingBox::Create(mesh->bounding_box.value(), 0xFF00C1));
    }
}

auto ExampleSandbox::ContextMenu() -> void {
    // Empty
}