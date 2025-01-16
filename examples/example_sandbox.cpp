// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_sandbox.hpp"

#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleSandbox::ExampleSandbox(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 6.0f);
    Add(camera_controls);

    auto ambient = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient);

    auto directional_light = DirectionalLight::Create(0xFFFFFF, 1.0f);
    directional_light->transform.Translate({2.0f, 2.0f, 2.0f});
    directional_light->SetDebugMode(true);
    Add(directional_light);

    auto sphere_geometry = SphereGeometry::Create();
    auto plane_geometry = PlaneGeometry::Create({3.0f, 3.0f});

    auto transparent_material = PhongMaterial::Create();
    transparent_material->transparent = true;
    transparent_material->opacity = 0.8f;
    transparent_material->color = 0x049EF4;

    auto opaque_material = PhongMaterial::Create();
    opaque_material->color = 0xEF798A;

    auto sphere_mesh = Mesh::Create(sphere_geometry, transparent_material);
    Add(sphere_mesh);

    auto plane_mesh = Mesh::Create(plane_geometry, opaque_material);
    plane_mesh->TranslateZ(-1.0f);
    Add(plane_mesh);
}

auto ExampleSandbox::Update(float delta) -> void {
    // TODO: implement.
}