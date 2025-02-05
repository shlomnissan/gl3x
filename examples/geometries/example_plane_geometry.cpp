// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_plane_geometry.hpp"

#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

#include <format>

#include <imgui.h>

using namespace engine;

ExamplePlaneGeometry::ExamplePlaneGeometry(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 3.0f);
    Add(camera_controls);

    auto ambient = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient);

    auto directional_light = DirectionalLight::Create(0xFFFFFF, 1.0f);
    directional_light->transform.Translate({2.0f, 2.0f, 2.0f});
    Add(directional_light);

    auto geometry = PlaneGeometry::Create(params_);

    auto base_material = PhongMaterial::Create();
    base_material->color = 0x049EF4;
    base_material->polygon_offset = {1.0f, 1.0f};
    base_material->two_sided = true;
    mesh_ = Mesh::Create(geometry, base_material);
    Add(mesh_);

    auto wireframe_material = FlatMaterial::Create();
    wireframe_material->wireframe = true;
    wireframe_material->two_sided = true;
    wireframe_material->fog = false;
    wireframes_ = Mesh::Create(geometry, wireframe_material);
    mesh_->Add(wireframes_);
}

auto ExamplePlaneGeometry::ContextMenu() -> void {
    static bool update_geometry = false;

    static const auto SliderFloat = [](
        std::string_view label,
        float& value,
        float min,
        float max)
    {
        ImGui::Text(label.data());
        ImGui::SetNextItemWidth(235);
        if (ImGui::SliderFloat(std::format("##{}", label).c_str(), &value, min, max)) {
            update_geometry = true;
        }
    };

    static const auto SliderUnsigned = [](
        std::string_view label,
        unsigned& value,
        unsigned min,
        unsigned max)
    {
        auto v = static_cast<int>(value);
        ImGui::Text(label.data());
        ImGui::SetNextItemWidth(235);
        if (ImGui::SliderInt(std::format("##{}", label).c_str(), &v, min, max)) {
            value = static_cast<unsigned>(v);
            update_geometry = true;
        }
    };

    SliderFloat("Width", params_.width, 1.0f, 5.0f);
    SliderFloat("Height", params_.height, 1.0f, 5.0f);
    SliderUnsigned("Width Segments", params_.width_segments, 1, 20);
    SliderUnsigned("Height Segments", params_.height_segments, 1, 20);

    if (update_geometry) {
        update_geometry = false;
        auto geometry = PlaneGeometry::Create(params_);
        mesh_->SetGeometry(geometry);
        wireframes_->SetGeometry(geometry);
    }
}