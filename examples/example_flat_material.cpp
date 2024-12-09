// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "example_flat_material.hpp"

#include <engine/core.hpp>
#include <engine/materials.hpp>
#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleFlatMaterial::ExampleFlatMaterial(std::shared_ptr<engine::Camera> camera) {
    auto geometry = BoxGeometry::Create({});
    auto material = FlatMaterial::Create();
    material->color = 0x47A8BD;
    material->cull_backfaces = false;
    mesh_ = Mesh::Create(geometry, material);

    auto point_light = PointLight::Create(0xf00ff0, 1.0f);
    point_light->transform.Translate({1.0f, 1.0f, 1.0f});
    point_light->SetDebugMode(true);
    Add(point_light);

    Add(mesh_);
}

auto ExampleFlatMaterial::Update(float delta) -> void {
    mesh_->transform.Rotate(Vector3::Up(), 1.0f * delta);
}