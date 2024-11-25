// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core/application_context.hpp>
#include <engine/geometry/box_geometry.hpp>
#include <engine/lights/lights.hpp>
#include <engine/materials/materials.hpp>
#include <engine/scene/camera_perspective.hpp>
#include <engine/scene/mesh.hpp>

#include <imgui.h>

class Application : public engine::ApplicationContext {
public:
    auto Configure() -> void override{
        params.vsync = false;
    }

    auto Setup() -> void override {
        ApplicationContext::Setup();

        window->SetTitle("Examples");
        renderer->SetClearColor({0.0f, 0.0f, 0.5f, 1.0f});

        scene = engine::Scene::Create();
        camera = engine::CameraPerspective::Create(60.0f, window->AspectRatio());
        camera->transform.Translate({0.0f, 0.0f, 2.0f});

        auto ambient_light = engine::AmbientLight::Create(0xffffff, 0.2f);
        scene->Add(ambient_light);

        auto directional_light = engine::DirectionalLight::Create(0xffffff, 1.0f);
        directional_light->transform.Translate({2.0f, 2.0f, 2.0f});
        directional_light->SetDebugMode(true);
        scene->Add(directional_light);

        auto geometry = engine::BoxGeometry::Create({});
        auto material = engine::PhongMaterial::Create();
        material->texture_map = engine::Texture2D::Create("assets/checker.png");
        mesh_ = engine::Mesh::Create(geometry, material);
        mesh_->transform.Scale(0.7f);

        scene->Add(mesh_);
    }

    auto Update(float delta) -> bool override {
        ImGui::Begin("Examples");
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