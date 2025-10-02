/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_model_loader.hpp"

#include "ui_helpers.hpp"

#include <gl3x/lights.hpp>
#include <gl3x/materials.hpp>

#include <print>

using namespace gl3x;
using namespace gl3x::math;

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

auto ExampleModelLoader::OnAttached(SharedContextPointer context) -> void {
    Add(OrbitControls::Create(context->camera, {
        .radius = 4.0f,
        .pitch = DegToRad(20.0f),
        .yaw = DegToRad(15.0f)
    }));

    context->mesh_loader->LoadAsync(
        "assets/mushroom.msh",
        [this](auto result) {
            if (result) {
                model_ = result.value();
                model_->SetScale(0.005f);
                model_->TranslateY(-0.4f);
                sphere_->Add(model_);
            } else {
                std::println(stderr, "{}", result.error());
            }
        }
    );

    context->texture_loader->LoadAsync(
        "assets/mushroms_Opacity_1002.tex",
        [this](auto result) {
            if (result) {
                alpha_map_ = result.value();
            } else {
                std::println(stderr, "{}", result.error());
            }
        }
    );
}

auto ExampleModelLoader::OnUpdate(float delta) -> void {
    if (!is_alpha_set && alpha_map_ != nullptr && model_ != nullptr) {
        auto x = static_cast<Mesh*>(model_->Children()[10].get());
        auto m = static_cast<PhongMaterial*>(x->GetMaterial().get());
        m->alpha_map = alpha_map_;
        m->transparent = true;
        is_alpha_set = true;
    }

    sphere_->RotateY(0.1f * delta);
}