/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_fog.hpp"

#include "ui_helpers.hpp"

#include <gl3x/core.hpp>
#include <gl3x/geometries.hpp>
#include <gl3x/lights.hpp>
#include <gl3x/materials.hpp>
#include <gl3x/nodes.hpp>

using namespace gl3x;

ExampleFog::ExampleFog() {
    auto geometry = BoxGeometry::Create();
    auto material = PhongMaterial::Create(0x049EF4);

    for (auto i = 0; i < 10; ++i) {
        auto box = Mesh::Create(geometry, material);
        box->TranslateZ(-1.5f * static_cast<float>(i));
        Add(box);
    }

    Add(AmbientLight::Create({
        .color = 0xFFFFFF,
        .intensity = 0.3f
    }));

    auto point_light = PointLight::Create({
        .color = 0xFFFFFF,
        .intensity = 1.0f,
        .attenuation = {
            .base = 1.0f,
            .linear = 0.0f,
            .quadratic = 0.0f
        }
    });
    point_light->transform.Translate({2.0f, 2.0f, 2.0f});
    Add(point_light);

    fog = LinearFog::Create(0x444444, 2.0f, 6.0f);
}

auto ExampleFog::OnAttached(SharedContextPointer context) -> void {
    Add(OrbitControls::Create(context->camera, {
        .radius = 3.0f,
        .pitch = math::DegToRad(25.0f),
        .yaw = math::DegToRad(-25.0f)
    }));
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

    if (fog->GetType() == FogType::LinearFog) {
        auto f = static_cast<LinearFog*>(fog.get());
        UISliderFloat("near", f->near, 0.0f, 20.0f, _, 160.0f);
        UISliderFloat("far", f->far, 0.0f, 20.0f, _, 160.0f);
    }

    if (fog->GetType() == FogType::ExponentialFog) {
        auto f = static_cast<ExponentialFog*>(fog.get());
        UISliderFloat("density", f->density, 0.0f, 1.0f, _, 160.0f);
    }
}