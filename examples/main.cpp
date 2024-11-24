// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/materials/flat_material.hpp"
#include <engine/core/application_context.hpp>
#include <engine/geometry/box_geometry.hpp>
#include <engine/materials/materials.hpp>
#include <engine/scene/camera_perspective.hpp>
#include <engine/scene/mesh.hpp>
#include <engine/scene/scene.hpp>

#include <imgui.h>

class Application : public engine::ApplicationContext {
public:
    auto Setup() -> void override {
        window_parameters.vsync = false;

        auto scene = engine::Scene::Create();
        SetScene(scene);

        auto camera = engine::CameraPerspective::Create(60.0f, 1.33f);
        SetCamera(camera);

        camera->transform.Translate({0.0f, 0.0f, 2.0f});

        auto geometry = engine::BoxGeometry::Create({});
        auto material = engine::FlatMaterial::Create();
        material->texture_map = engine::Texture2D::Create("assets/checker.png");

        mesh_ = engine::Mesh::Create(geometry, material);
        mesh_->transform.Scale(0.9f);

        scene->Add(mesh_);
    }

    auto Update(float delta) -> bool override {
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a minimal UI example.");
        ImGui::End();

        mesh_->transform.Rotate(engine::Vector3::Up(), 0.7f * delta);
        mesh_->transform.Rotate(engine::Vector3::Right(), 0.7f * delta);

        return true;
    }

private:
    std::shared_ptr<engine::Mesh> mesh_;
};

auto main() -> int {
    auto app = Application {};
    app.Start();

    return 0;
}