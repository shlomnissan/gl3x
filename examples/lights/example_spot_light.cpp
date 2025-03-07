// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_spot_light.hpp"

#include "ui_helpers.hpp"

#include <engine/geometries.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

#include <imgui.h>

using namespace engine;

ExampleSpotLight::ExampleSpotLight(std::shared_ptr<engine::Camera> camera) {
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

    auto mesh = Mesh::Create(
        PlaneGeometry::Create({.width = 3, .height = 3}),
        PhongMaterial::Create(0xCCCCCC)
    );

    mesh->GetMaterial()->polygon_offset = {-0.5f, 0.5f};
    mesh->transform.Rotate(Vector3::Right(), math::DegToRad(-90.0f));
    Add(mesh);

    Add(AmbientLight::Create(0xFFFFFF, 0.15f));
    spot_light_ = SpotLight::Create(0xFFFFFF, 1.0f);
    spot_light_->transform.Translate({2.0f, 2.0f, -1.0f});
    spot_light_->angle = math::DegToRad(10.0f);
    spot_light_->distance = 4.0f;
    spot_light_->SetDebugMode(true);
    Add(spot_light_);
}

auto ExampleSpotLight::ContextMenu() -> void {
    auto _ = true;

    UIColor("color", &spot_light_->color[0], _);
    UISliderFloat("intensity", spot_light_->intensity, 0.0f, 1.0f, _, 160.0f);
}