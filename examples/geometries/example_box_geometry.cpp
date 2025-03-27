// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_box_geometry.hpp"

#include "ui_helpers.hpp"

#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;
using namespace engine::math;

ExampleBoxGeometry::ExampleBoxGeometry(std::shared_ptr<engine::Camera> camera) {
    Add(CameraOrbit::Create(camera, 3.0f, DegToRad(15.0f), DegToRad(45.0f)));
    Add(AmbientLight::Create(0xFFFFFF, 0.3f));

    auto point_light = PointLight::Create(0xFFFFFF, 1.0f);
    point_light->transform.Translate({2.0f, 2.0f, -2.0f});
    Add(point_light);

    auto geometry = BoxGeometry::Create(params_);

    auto base_material = PhongMaterial::Create(0xCCCCCC);
    base_material->flat_shaded = true;
    base_material->polygon_offset = {1.0f, 1.0f};

    mesh_ = Mesh::Create(geometry, base_material);
    Add(mesh_);

    auto wireframe_material = FlatMaterial::Create();
    wireframe_material->wireframe = true;
    wireframe_material->fog = false;
    wireframes_ = Mesh::Create(geometry, wireframe_material);
    mesh_->Add(wireframes_);
}

auto ExampleBoxGeometry::ContextMenu() -> void {
    static bool dirty = false;

    UISliderFloat("width", params_.width, 1.0f, 5.0f, dirty);
    UISliderFloat("height", params_.height, 1.0f, 5.0f, dirty);
    UISliderFloat("depth", params_.depth, 1.0f, 5.0f, dirty);
    UISliderUnsigned("width_segments", params_.width_segments, 1, 20, dirty);
    UISliderUnsigned("height_segments", params_.height_segments, 1, 20, dirty);
    UISliderUnsigned("depth_segments", params_.depth_segments, 1, 20, dirty);

    if (dirty) {
        dirty = false;
        auto geometry = BoxGeometry::Create(params_);
        mesh_->SetGeometry(geometry);
        wireframes_->SetGeometry(geometry);
    }
}