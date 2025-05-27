// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_frustum_culling_test.hpp"

#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleFrustumCullingTest::ExampleFrustumCullingTest(std::shared_ptr<engine::Camera> camera) {
    show_context_menu_ = false;

    Add(OrbitControls::Create(camera, {.radius = 3.0f}));

    Add(AmbientLight::Create({
        .color = 0xFFFFFF,
        .intensity = .3f
    }));

    auto point_light = PointLight::Create(0xFFFFFF, 1.0f);
    point_light->transform.Translate({0.0f, 0.0f, 30.0f});
    point_light->SetDebugMode(true);
    Add(point_light);

    const auto geometry = BoxGeometry::Create({1.0f, 1.0f, 1.0f});
    const auto material = PhongMaterial::Create(0x049EF4);
    for (auto i = 0; i < 50; ++i) {
        for (auto j = 0; j < 50; ++j) {
            auto box = Mesh::Create(geometry, material);
            box->transform.Translate({i * 2.0f - 49.0f, j * 2.0f - 49.0f, 0.0f});
            boxes_[i * 50 + j] = box;
            Add(box);
        }
    }
}

auto ExampleFrustumCullingTest::OnUpdate(float delta) -> void {
    for (const auto& b : boxes_) {
        b->RotateX(1.0f * delta);
        b->RotateY(1.0f * delta);
    }
}

auto ExampleFrustumCullingTest::ContextMenu() -> void {
    // Empty
}