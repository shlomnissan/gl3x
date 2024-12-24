// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "example_geometries_sphere.hpp"

#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleGeometriesSphere::ExampleGeometriesSphere(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 3.0f);
    Add(camera_controls);

    auto ambient = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient);

    auto directional_light = DirectionalLight::Create(0xFFFFFF, 1.0f);
    directional_light->transform.Translate({2.0f, 2.0f, 2.0f});
    Add(directional_light);
}

auto ExampleGeometriesSphere::Update(float delta) -> void {
    // TODO: implement update logic
}