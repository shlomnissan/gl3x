/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_mesh_instancing.hpp"

#include <gleam/geometries.hpp>
#include <gleam/lights.hpp>
#include <gleam/materials.hpp>
#include <gleam/math.hpp>

using namespace gleam;

ExampleMeshInstancing::ExampleMeshInstancing() {
    show_context_menu_ = false;

    auto ambient_light = AmbientLight::Create({.color = 0xFFFFFF, .intensity = .3f});
    Add(ambient_light);

    auto point_light = PointLight::Create({.color = 0xFFFFFF, .intensity = 1.0f});
    point_light->transform.Translate({0.0f, 0.0f, 5.0f});
    Add(point_light);

    const auto geometry = CubeGeometry::Create({1.0f, 1.0f, 1.0f});
    const auto material = PhongMaterial::Create(0x049EF4);
    boxes_ = InstancedMesh::Create(geometry, material, 2);
    Add(boxes_);

    for (auto i = 0; i < 2; ++i) {
        auto t = Transform3 {};
        t.SetPosition({i * 2.0f - 1.0f, 0.0f, 0.0f});
        boxes_->SetTransformAt(t, i);
    }
}

auto ExampleMeshInstancing::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {.radius = 5.0f}));
}

auto ExampleMeshInstancing::OnUpdate(float delta) -> void {
    boxes_->RotateY(1.0f * delta);
}

auto ExampleMeshInstancing::ContextMenu() -> void {
    // Empty
}