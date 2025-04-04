// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_flat_material.hpp"

#include "ui_helpers.hpp"

#include <engine/geometries.hpp>
#include <engine/resources.hpp>
#include <engine/loaders.hpp>
#include <engine/textures.hpp>

using namespace engine;

ExampleFlatMaterial::ExampleFlatMaterial(std::shared_ptr<engine::Camera> camera) {
    Add(CameraOrbit::Create(camera, 3.0f));

    auto image_loader = engine::ImageLoader {};
    image_loader.LoadAsync("assets/checker.png", [this](auto image) {
        image_ = std::move(image);
    });

    fog = ExponentialFog::Create(0x444444, 0.3f);

    auto geometry = BoxGeometry::Create();
    material_ = FlatMaterial::Create();
    material_->color = 0x049EF4;
    material_->fog = false;
    mesh_ = Mesh::Create(geometry, material_);
    Add(mesh_);
}

auto ExampleFlatMaterial::Update(float delta) -> void {
    mesh_->transform.Rotate(Vector3::Up(), 1.0f * delta);
    mesh_->transform.Rotate(Vector3::Right(), 1.0f * delta);
}

auto ExampleFlatMaterial::ContextMenu() -> void {
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
        if (str == "checkerboard") material_->texture_map = engine::Texture2D::Create(image_);
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