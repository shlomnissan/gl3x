// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_point_light.hpp"

#include "ui_helpers.hpp"

#include <engine/geometries.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

#include <imgui.h>

using namespace engine;

ExamplePointLight::ExamplePointLight(std::shared_ptr<engine::Camera> camera) {
    Add(CameraOrbit::Create(
        camera, 5.0f,
        math::DegToRad(25.0f),
        math::DegToRad(45.0f)
    ));

    Add(Grid::Create({
        .size = 4,
        .divisions = 16,
        .color = 0x333333
    }));

    const auto mesh = Mesh::Create(
        SphereGeometry::Create({
            .radius = 0.5f,
            .width_segments = 32,
            .height_segments = 32
        }),
        PhongMaterial::Create(0xCCCCCC)
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

    UIColor("color", &point_light_->color[0], _);
    UISliderFloat("intensity", point_light_->intensity, 0.0f, 1.0f, _, 160.0f);
}