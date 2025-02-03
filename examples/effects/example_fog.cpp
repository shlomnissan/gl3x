// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_fog.hpp"

#include <engine/core.hpp>
#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

#include <imgui.h>

using namespace engine;

ExampleFog::ExampleFog(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(
        camera, 3.0f,
        math::DegToRad(25.0f),
        math::DegToRad(-25.0f)
    );
    Add(camera_controls);

    auto geometry = BoxGeometry::Create();
    auto material = PhongMaterial::Create();
    material->color = 0x049EF4;

    for (auto i = 0; i < 10; ++i) {
        auto box = Mesh::Create(geometry, material);
        box->TranslateZ(-1.5f * static_cast<float>(i));
        Add(box);
    }

    auto ambient_light = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient_light);

    auto point_light = PointLight::Create(0xFFFFFF, 1.0f);
    point_light->transform.Translate({2.0f, 2.0f, 2.0f});
    Add(point_light);

    fog = LinearFog::Create(0x444444, 2.0f, 6.0f);
}

auto ExampleFog::ContextMenu() -> void {
    ImGui::Text("Fog");
}