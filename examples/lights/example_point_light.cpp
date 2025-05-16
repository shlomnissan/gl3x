// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_point_light.hpp"

#include "ui_helpers.hpp"

#include <engine/geometries.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExamplePointLight::ExamplePointLight(std::shared_ptr<engine::Camera> camera) {
    Add(CameraOrbit::Create(camera, {
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
    point_light_ = PointLight::Create(0xFFFFFF, 1.0f);
    point_light_->transform.Translate({1.0f, 2.0f, -2.0f});
    point_light_->SetDebugMode(true);
    Add(point_light_);
}

auto ExamplePointLight::ContextMenu() -> void {
    auto _ = true;

    UIColor("color", &point_light_->color[0], _, "light-color");
    UISliderFloat("intensity", point_light_->intensity, 0.0f, 1.0f, _, 160.0f);
    UIText("Attenuation");
    UISliderFloat("base", point_light_->attenuation.base, 0.0f, 2.0f, _, 160.0f);
    UISliderFloat("linear", point_light_->attenuation.linear, 0.0f, 1.0f, _, 160.0f);
    UISliderFloat("quadratic", point_light_->attenuation.quadratic, 0.0f, 2.0f, _, 160.0f);

    UISeparator();

    UIText("Material");
    UIColor("color", &phong_material_->color[0], _, "material-color");
    UIColor("specular", &phong_material_->specular[0], _);
    UISliderFloat("shininess", phong_material_->shininess, 0.0f, 128.0f, _, 160.0f);
}