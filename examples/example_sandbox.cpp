// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_sandbox.hpp"

#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>

#include <cmath>

using namespace engine;

ExampleSandbox::ExampleSandbox(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 3.0f);
    Add(camera_controls);

    auto ambient = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient);

    auto point_light = PointLight::Create(0xFFFFFF, 1.0f);
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
    start_point->transform.Translate(start_);
    Add(start_point);

    auto end_point = Mesh::Create(sphere, background_material);
    end_point->transform.Translate(end_);
    Add(end_point);

    active_point_ = Mesh::Create(sphere, PhongMaterial::Create(0xFF0000));
    active_point_->transform.Translate(end_);
    Add(active_point_);
}

auto ExampleSandbox::Update(float delta) -> void {
    elapsed_time_ += delta;
    auto t = elapsed_time_ / 2.0f;
    if (t >= 1.0f) {
        t = 0.0f;
        elapsed_time_ = 0.0f;
        std::swap(start_, end_);
    }
    auto p = Lerp(start_, end_, t);
    active_point_->transform.SetPosition(p);
}

auto ExampleSandbox::ContextMenu() -> void {
    // Empty
}