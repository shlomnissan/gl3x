// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_sphere_geometry.hpp"

#include "ui_helpers.hpp"

#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleSphereGeometry::ExampleSphereGeometry(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 3.0f);
    Add(camera_controls);

    auto ambient = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient);

    auto directional_light = DirectionalLight::Create(0xFFFFFF, 1.0f);
    directional_light->transform.Translate({2.0f, 2.0f, 2.0f});
    Add(directional_light);

    auto geometry = SphereGeometry::Create(params_);

    auto base_material = PhongMaterial::Create();
    base_material->color = 0x049EF4;
    base_material->polygon_offset = {1.0f, 1.0f};

    mesh_ = Mesh::Create(geometry, base_material);
    Add(mesh_);

    auto wireframe_material = FlatMaterial::Create();
    wireframe_material->wireframe = true;
    wireframe_material->fog = false;
    wireframes_ = Mesh::Create(geometry, wireframe_material);
    mesh_->Add(wireframes_);
}

auto ExampleSphereGeometry::ContextMenu() -> void {
    static bool dirty = false;

    UISliderFloat("radius", params_.radius, 0.5f, 2.0f, dirty);
    UISliderUnsigned("width_segments", params_.width_segments, 3, 64, dirty);
    UISliderUnsigned("height_segments", params_.height_segments, 2, 64, dirty);
    UISliderFloat("phi_start", params_.phi_start, 0.0f, math::two_pi, dirty);
    UISliderFloat("phi_length", params_.phi_length, 0.0f, math::two_pi, dirty);
    UISliderFloat("theta_start", params_.theta_start, 0.0f, math::two_pi, dirty);
    UISliderFloat("theta_length", params_.theta_length, 0.0f, math::two_pi, dirty);

    if (dirty) {
        dirty = false;
        auto geometry = SphereGeometry::Create(params_);
        mesh_->SetGeometry(geometry);
        wireframes_->SetGeometry(geometry);
    }
}