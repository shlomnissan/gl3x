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
    boxes_ = InstancedMesh::Create(geometry, material, 1);
    Add(boxes_);
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