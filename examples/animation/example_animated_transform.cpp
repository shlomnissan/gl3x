/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_animated_transform.hpp"

#include <gleam/geometries.hpp>
#include <gleam/lights.hpp>

#include <cmath>

using namespace gleam;

ExampleAnimatedTransform::ExampleAnimatedTransform() {
    show_context_menu_ = false;

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
    point_light->transform.Translate({0.0f, 0.0f, 30.0f});
    point_light->SetDebugMode(true);
    Add(point_light);

    auto sphere = SphereGeometry::Create({
        .radius = 0.3f,
        .width_segments = 32,
        .height_segments = 32
    });

    auto background_material = PhongMaterial::Create(0x777777);
    background_material->depth_test = false;

    auto start_point = Mesh::Create(sphere, background_material);
    start_point->transform.Translate(start_pos_);
    Add(start_point);

    auto end_point = Mesh::Create(sphere, background_material);
    end_point->transform.Translate(end_pos_);
    end_point->SetScale(0.5f);
    Add(end_point);

    active_material_ = PhongMaterial::Create(start_color_);
    active_point_ = Mesh::Create(sphere, active_material_);
    active_point_->transform.Translate(end_pos_);
    Add(active_point_);
}

auto ExampleAnimatedTransform::OnAttached(SharedContextPointer context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {.radius = 3.0f}));
}

auto ExampleAnimatedTransform::OnUpdate(float delta) -> void {
    elapsed_time_ += delta;
    auto t = elapsed_time_ / 2.0f;
    if (t >= 1.0f) {
        t = 0.0f;
        elapsed_time_ = 0.0f;
        std::swap(start_pos_, end_pos_);
        std::swap(start_color_, end_color_);
        std::swap(start_scale_, end_scale_);
    }

    active_point_->transform.SetPosition(Lerp(start_pos_, end_pos_, t));
    active_point_->SetScale(Lerp(start_scale_, end_scale_, t));
    active_material_->color = Lerp(start_color_, end_color_, t);
}