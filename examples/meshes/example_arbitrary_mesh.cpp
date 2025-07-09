/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_arbitrary_mesh.hpp"

#include "ui_helpers.hpp"

#include <gleam/cameras.hpp>
#include <gleam/lights.hpp>

using namespace gleam;
using namespace gleam::math;

ExampleArbitraryMesh::ExampleArbitraryMesh(std::shared_ptr<gleam::Camera> camera) {
    show_context_menu_ = false;

    Add(OrbitControls::Create(camera.get(), {
        .radius = 4.0f,
        .pitch = DegToRad(5.0f),
        .yaw = DegToRad(15.0f)
    }));

    Add(AmbientLight::Create({
        .color = 0xFFFFFF,
        .intensity = 0.3f
    }));

    auto point_light = PointLight::Create({
        .color = 0xFFFFFF,
        .intensity = 1.0f,
        .attenuation = {
            .base = 1.0f,
            .linear = 0.0f,
            .quadratic = 0.0f
        }
    });
    point_light->transform.Translate({2.0f, 2.0f, 4.0f});
    point_light->SetDebugMode(true);
    Add(point_light);
}

auto ExampleArbitraryMesh::OnAttached(gleam::SharedContext* context) -> void {
    context->Loaders().Mesh->LoadAsync(
        "assets/bunny.msh",
        [this](auto result) {
            if (result) {
                mesh_ = result.value();
                Add(mesh_);
            }
        }
    );
}

auto ExampleArbitraryMesh::ContextMenu() -> void {
    // Empty
}