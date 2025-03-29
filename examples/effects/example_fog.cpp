// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_fog.hpp"

#include "ui_helpers.hpp"

#include <engine/core.hpp>
#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleFog::ExampleFog(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(
        camera, 3.0f,
        math::DegToRad(25.0f),
        math::DegToRad(-25.0f)
    );
    Add(camera_controls);

    auto geometry = BoxGeometry::Create();
    auto material = PhongMaterial::Create();
    material->color = 0x049EF4;

    for (auto i = 0; i < 10; ++i) {
        auto box = Mesh::Create(geometry, material);
        box->TranslateZ(-1.5f * static_cast<float>(i));
        Add(box);
    }

    auto ambient_light = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient_light);

    auto point_light = PointLight::Create(0xFFFFFF, 1.0f);
    point_light->transform.Translate({2.0f, 2.0f, 2.0f});
    Add(point_light);

    fog = LinearFog::Create(0x444444, 2.0f, 6.0f);
}

auto ExampleFog::ContextMenu() -> void {
    auto _ = true;
    static auto curr_fog_function = std::string {"linear"};
    static auto fog_function = std::array<const char*, 2> {
        "linear", "exponential"
    };

    UIColor("color", &fog->color[0], _);
    UIDropDown("function", fog_function, curr_fog_function,
      [this](std::string_view str) {
        curr_fog_function = str;
        if (str == "linear") fog = LinearFog::Create(fog->color, 2.0f, 6.0f);
        if (str == "exponential") fog = ExponentialFog::Create(fog->color, 0.2f);
    });

    if (auto linear_fog = dynamic_cast<LinearFog*>(fog.get())) {
        UISliderFloat("near", linear_fog->near, 0.0f, 20.0f, _, 160.0f);
        UISliderFloat("far", linear_fog->far, 0.0f, 20.0f, _, 160.0f);
    }

    if (auto exponential_fog = dynamic_cast<ExponentialFog*>(fog.get())) {
        UISliderFloat("density", exponential_fog->density, 0.0f, 1.0f, _, 160.0f);
    }
}