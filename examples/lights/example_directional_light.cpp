// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_directional_light.hpp"

#include "ui_helpers.hpp"

#include <engine/geometries.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleDirectionalLight::ExampleDirectionalLight(std::shared_ptr<engine::Camera> camera) {
    Add(OrbitControls::Create(camera, {
        .radius = 5.0f,
        .pitch = math::DegToRad(25.0f),
        .yaw = math::DegToRad(45.0f)
    }));

    Add(Grid::Create({
        .size = 4,
        .divisions = 16,
        .color = 0x333333
    }));

    phong_material_ = PhongMaterial::Create(0xCCCCCC);
    const auto mesh = Mesh::Create(
        SphereGeometry::Create({
            .radius = 0.5f,
            .width_segments = 32,
            .height_segments = 32
        }),
        phong_material_
    );

    mesh->transform.Translate({0.0f, 0.5f, 0.0f});
    Add(mesh);

    Add(AmbientLight::Create(0xFFFFFF, 0.15f));
    directional_light_ = DirectionalLight::Create(0xFFFFFF, 1.0f);
    directional_light_->transform.Translate({2.0f, 2.0f, -2.0f});
    directional_light_->target = mesh;
    directional_light_->SetDebugMode(true);
    Add(directional_light_);
}

auto ExampleDirectionalLight::ContextMenu() -> void {
    auto _ = true;

    UIColor("color", &directional_light_->color[0], _, "light-color");
    UISliderFloat("intensity", directional_light_->intensity, 0.0f, 1.0f, _, 160.0f);

    UISeparator();

    UIText("Material");
    UIColor("color", &phong_material_->color[0], _, "material-color");
    UIColor("specular", &phong_material_->specular[0], _);
    UISliderFloat("shininess", phong_material_->shininess, 0.0f, 128.0f, _, 160.0f);
}