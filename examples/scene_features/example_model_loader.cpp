/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_model_loader.hpp"

#include "ui_helpers.hpp"

#include <gleam/lights.hpp>
#include <gleam/materials.hpp>

using namespace gleam;
using namespace gleam::math;

ExampleModelLoader::ExampleModelLoader() {
    show_context_menu_ = false;

    sphere_ = Mesh::Create(
        SphereGeometry::Create({.radius = 5.0f}),
        PhongMaterial::Create(0x000011)
    );
    sphere_->GetMaterial()->two_sided = true;
    Add(sphere_);

    sphere_->Add(AmbientLight::Create({
        .color = 0xFFFFFF,
        .intensity = 0.3f
    }));

    auto light_0 = PointLight::Create({.color = 0xFFFFFF, .intensity = 1.0f});
    light_0->transform.Translate({2.0f, 2.5f, 4.0f});
    sphere_->Add(light_0);

    auto light_1 = PointLight::Create({.color = 0xFAA916, .intensity = 1.0f});
    light_1->transform.Translate({-2.0f, 2.5f, -3.0f});
    sphere_->Add(light_1);
}

auto ExampleModelLoader::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {
        .radius = 4.0f,
        .pitch = DegToRad(20.0f),
        .yaw = DegToRad(15.0f)
    }));

    context->Loaders().Mesh->LoadAsync(
        "assets/mushroom.msh",
        [this](auto result) {
            if (result) {
                mesh_ = result.value();
                mesh_->SetScale(0.005f);
                mesh_->TranslateY(-0.4f);
                sphere_->Add(mesh_);
            }
        }
    );
}

auto ExampleModelLoader::OnUpdate(float delta) -> void {
    sphere_->RotateY(0.1f * delta);
}

auto ExampleModelLoader::ContextMenu() -> void {
    // Empty
}