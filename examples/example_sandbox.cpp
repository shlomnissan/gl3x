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
    mesh->SetScale({1.0f, 2.0f, 1.0f});
    mesh->RotateZ(0.5f);
    Add(mesh);

    auto box = Box3 {};
    auto geoemetry = mesh->GetGeometry();
    const auto& vertex_data = geoemetry->VertexData();
    const auto stride = geoemetry->Stride();
    for (auto i = 0; i < vertex_data.size(); i += stride) {
        box.ExpandWithPoint({
            vertex_data[i],
            vertex_data[i + 1],
            vertex_data[i + 2]
        });
    }

    box.ApplyTransform(mesh->GetWorldTransform());
    Add(BoundingBox::Create(box, 0xFF00C1));
}

auto ExampleSandbox::ContextMenu() -> void {
    // Empty
}