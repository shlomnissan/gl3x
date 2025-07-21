/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_unlit_material.hpp"

#include "ui_helpers.hpp"

#include <gleam/geometries.hpp>
#include <gleam/loaders.hpp>
#include <gleam/textures.hpp>

using namespace gleam;

ExampleUnlitMaterial::ExampleUnlitMaterial() {
    auto geometry = CubeGeometry::Create();
    material_ = UnlitMaterial::Create(0x049EF4);
    mesh_ = Mesh::Create(geometry, material_);
    Add(mesh_);
}

auto ExampleUnlitMaterial::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {.radius = 3.0f}));

    context->Loaders().Texture->LoadAsync(
        "assets/checker.tex",
        [this](auto result) {
            if (result) texture_ = result.value();
        }
    );
}

auto ExampleUnlitMaterial::OnUpdate(float delta) -> void {
    mesh_->transform.Rotate(Vector3::Up(), 1.0f * delta);
    mesh_->transform.Rotate(Vector3::Right(), 1.0f * delta);
}

auto ExampleUnlitMaterial::ContextMenu() -> void {
    auto _ = false;
    static auto curr_texture = std::string {"none"};
    static auto textures = std::array<const char*, 2> {
        "none", "checkerboard"
    };

    UIColor("color", &material_->color[0], _);
    UIDropDown("texture", textures, curr_texture,
      [this](std::string_view str) {
        curr_texture = str;
        if (str == "none") material_->texture_map = nullptr;
        if (str == "checkerboard") material_->texture_map = texture_;
    });

    UISeparator();

    UICheckbox("transparent", material_->transparent, _);
    UISliderFloat("opacity", material_->opacity, 0.0f, 1.0f, _, 160.0f);

    UISeparator();

    UICheckbox("depth_test", material_->depth_test, _);
    UICheckbox("flat_shaded", material_->flat_shaded, _);
    UICheckbox("fog", material_->fog, _);
    UICheckbox("two_sided", material_->two_sided, _);
    UICheckbox("wireframe", material_->wireframe, _);
}