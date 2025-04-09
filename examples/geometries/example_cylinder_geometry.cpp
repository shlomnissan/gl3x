// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_cylinder_geometry.hpp"

#include "ui_helpers.hpp"

#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;
using namespace engine::math;

ExampleCylinderGeometry::ExampleCylinderGeometry(std::shared_ptr<engine::Camera> camera) {
    Add(CameraOrbit::Create(camera, 2.5f, DegToRad(15.0f), DegToRad(45.0f)));
    Add(AmbientLight::Create(0xFFFFFF, 0.2f));

    auto point_light = PointLight::Create(0xFFFFFF, 1.0f);
    point_light->transform.Translate({2.0f, 2.0f, 2.0f});
    Add(point_light);

    params_.radius_top = 0.4f;
    params_.radius_bottom = 0.4f;

    auto geometry = CylinderGeometry::Create(params_);

    auto base_material = PhongMaterial::Create(0xCCCCCC);
    base_material->flat_shaded = true;
    base_material->two_sided = true;
    base_material->polygon_offset = {1.0f, 1.0f};

    mesh_ = Mesh::Create(geometry, base_material);
    Add(mesh_);

    auto wireframe_material = FlatMaterial::Create();
    wireframe_material->wireframe = true;
    wireframe_material->fog = false;
    wireframe_material->two_sided = true;
    wireframes_ = Mesh::Create(geometry, wireframe_material);
    mesh_->Add(wireframes_);
}

auto ExampleCylinderGeometry::ContextMenu() -> void {
    static bool dirty = false;

    UISliderFloat("radius_top", params_.radius_top, 0.0f, 1.0f, dirty);
    UISliderFloat("radius_bottom", params_.radius_bottom, 0.0f, 1.0f, dirty);
    UISliderFloat("height", params_.height, 1.0f, 5.0f, dirty);
    UISliderUnsigned("radial_segments", params_.radial_segments, 3, 64, dirty);
    UISliderUnsigned("height_segments", params_.height_segments, 1, 20, dirty);
    UICheckbox("open_ended", params_.open_ended, dirty);

    if (dirty) {
        dirty = false;
        auto geometry = CylinderGeometry::Create(params_);
        mesh_->geometry = geometry;
        wireframes_->geometry = geometry;
    }
}