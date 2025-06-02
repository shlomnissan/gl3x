/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_blending.hpp"

#include "ui_helpers.hpp"

#include <gleam/geometries.hpp>
#include <gleam/lights.hpp>
#include <gleam/resources.hpp>

using namespace gleam;

ExampleBlending::ExampleBlending(std::shared_ptr<gleam::Camera> camera) {
    const auto camera_controls = OrbitControls::Create(camera, {.radius = 3.0f});
    Add(camera_controls);

    auto plane_geometry = PlaneGeometry::Create({.width = 2.0f, .height = 2.0f});
    auto opaque_material = PhongMaterial::Create();
    auto plane = Mesh::Create(plane_geometry, opaque_material);
    opaque_material->color = 0xE5BEED;
    opaque_material->two_sided = true;
    plane->TranslateZ(-0.5f);
    Add(plane);

    auto sphere_geometry = SphereGeometry::Create({.radius = 0.5f});
    transparent_material_ = PhongMaterial::Create();
    auto sphere = Mesh::Create(sphere_geometry, transparent_material_);
    transparent_material_->color = 0x049EF4;
    transparent_material_->transparent = true;
    transparent_material_->opacity = 0.9f;
    sphere->TranslateX(0.7f);
    Add(sphere);

    Add(AmbientLight::Create({
        .color = 0xFFFFFF,
        .intensity = .3f
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
}

auto ExampleBlending::ContextMenu() -> void {
    auto _ = true;
    static auto curr_blend_mode = std::string {"normal"};
    static auto blending_modes = std::array<const char*, 5> {
        "none", "normal", "additive", "subtractive", "multiply"
    };

    UIDropDown("mode", blending_modes, curr_blend_mode,
      [this](std::string_view str) {
        using enum Blending;
        curr_blend_mode = str;
        if (str == "none") transparent_material_->blending = None;
        if (str == "normal") transparent_material_->blending = Normal;
        if (str == "additive") transparent_material_->blending = Additive;
        if (str == "subtractive") transparent_material_->blending = Subtractive;
        if (str == "multiply") transparent_material_->blending = Multiply;
    });

    UISliderFloat("opacity", transparent_material_->opacity, 0.0f, 1.0f, _, 160.0f);
}