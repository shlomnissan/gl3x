// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_cone_geometry.hpp"

#include "helpers.hpp"

#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleConeGeometry::ExampleConeGeometry(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 3.0f);
    Add(camera_controls);

    auto ambient = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient);

    auto directional_light = DirectionalLight::Create(0xFFFFFF, 1.0f);
    directional_light->transform.Translate({2.0f, 2.0f, 2.0f});
    Add(directional_light);

    params_.radius = 0.5f;
    auto geometry = ConeGeometry::Create(params_);

    auto base_material = PhongMaterial::Create();
    base_material->color = 0x049EF4;
    base_material->polygon_offset = {1.0f, 1.0f};

    mesh_ = Mesh::Create(geometry, base_material);
    Add(mesh_);

    auto wireframe_material = FlatMaterial::Create();
    wireframe_material->wireframe = true;
    wireframe_material->two_sided = true;
    wireframe_material->fog = false;
    wireframes_ = Mesh::Create(geometry, wireframe_material);
    mesh_->Add(wireframes_);
}

auto ExampleConeGeometry::ContextMenu() -> void {
    static bool dirty = false;

    UISliderFloat("radius", params_.radius, 0.0f, 1.0f, dirty);
    UISliderFloat("height", params_.height, 0.1f, 5.0f, dirty);
    UISliderUnsigned("radial_segments", params_.radial_segments, 3, 64, dirty);
    UISliderUnsigned("height_segments", params_.height_segments, 1, 20, dirty);

    if (dirty) {
        dirty = false;
        auto geometry = ConeGeometry::Create(params_);
        mesh_->SetGeometry(geometry);
        wireframes_->SetGeometry(geometry);
    }
}