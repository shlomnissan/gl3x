// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_arbitrary_mesh.hpp"

#include "ui_helpers.hpp"

#include <engine/lights.hpp>
#include <engine/resources.hpp>

using namespace engine;
using namespace engine::math;

ExampleArbitraryMesh::ExampleArbitraryMesh(std::shared_ptr<engine::Camera> camera) {
    show_context_menu_ = false;

    Add(CameraOrbit::Create(camera, {
        .radius = 4.0f,
        .pitch = DegToRad(5.0f),
        .yaw = DegToRad(15.0f)
    }));

    Add(AmbientLight::Create(0xFFFFFF, 0.3f));

    auto point_light = PointLight::Create(0xFFFFFF, 1.0f);
    point_light->transform.Translate({2.0f, 2.0f, 4.0f});
    point_light->SetDebugMode(true);
    Add(point_light);
}

auto ExampleArbitraryMesh::OnAttached() -> void {
    this->Context()->Loaders().Mesh->LoadAsync(
        "assets/bunny.obj",
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