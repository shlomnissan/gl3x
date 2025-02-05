// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_fog.hpp"

#include <engine/core.hpp>
#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

#include <cstring>
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
    ImGui::ColorEdit3("Fog Color", &(fog->color[0]));

    ImGui::Text("Fog Function");
    ImGui::SetNextItemWidth(235);
    static auto curr_fog_function = "Linear";
    if (ImGui::BeginCombo("##FogFunction", curr_fog_function)) {
        for (const auto& fog_function : fog_function_) {
            auto is_selected = (curr_fog_function == fog_function);
            if (ImGui::Selectable(fog_function, is_selected)) {
                curr_fog_function = fog_function;
                if (std::strcmp(curr_fog_function, "Linear") == 0) {
                    fog = LinearFog::Create(fog->color, 2.0f, 6.0f);
                }
                if (std::strcmp(curr_fog_function, "Exponential") == 0) {
                    fog = ExponentialFog::Create(fog->color, 0.2f);
                }
            }
        }
        ImGui::EndCombo();
    }

    if (auto linear_fog = dynamic_cast<LinearFog*>(fog.get())) {
        ImGui::SliderFloat("Near", &(linear_fog->near), 0.0f, 20.0f);
        ImGui::SliderFloat("Far", &(linear_fog->far), 0.0f, 20.0f);
    }

    if (auto exponential_fog = dynamic_cast<ExponentialFog*>(fog.get())) {
        ImGui::SliderFloat("Density", &(exponential_fog->density), 0.0f, 1.0f);
    }
}