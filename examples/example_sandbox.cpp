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

    auto box = geometry->BoundingBox();
    box.ApplyTransform(mesh->GetWorldTransform());
    Add(BoundingBox::Create(box, 0xFF00C1));

    auto point_geometry = SphereGeometry::Create({0.05f});
    auto point_material = FlatMaterial::Create({0x000000});
    auto point = Mesh::Create(point_geometry, point_material);
    point->TranslateX(2.0f);
    point->TranslateY(2.0f);
    Add(point);

    auto sphere = Sphere {0.0f, 0.0f};
    sphere.ExpandWithPoint({2.0f, 2.0f, 0.0f});
    auto bounding_sphere = BoundingSphere::Create(sphere, 0xEEC584);
    Add(bounding_sphere);
}

auto ExampleSandbox::ContextMenu() -> void {
    // Empty
}