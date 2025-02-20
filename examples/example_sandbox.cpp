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

    const auto geometry = BoxGeometry::Create();
    const auto material = FlatMaterial::Create();
    material->color = 0x049EF4;

    auto mesh = Mesh::Create(geometry, material);
    mesh->CreateBoundingBox();
    mesh->SetScale({1.0f, 2.0f, 1.0f});
    mesh->RotateZ(0.5f);
    Add(mesh);

    if (mesh->bounding_box.has_value()) {
        auto box = mesh->bounding_box.value();
        box.ApplyTransform(mesh->GetWorldTransform());
        Add(BoundingBox::Create(box, 0xFF00C1));
    }
}

auto ExampleSandbox::ContextMenu() -> void {
    // Empty
}