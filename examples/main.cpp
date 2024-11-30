// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/vector3.hpp"
#include <engine/core/application_context.hpp>
#include <engine/geometry/box_geometry.hpp>
#include <engine/lights/lights.hpp>
#include <engine/materials/materials.hpp>
#include <engine/resources/camera_orbit.hpp>
#include <engine/scene/camera_perspective.hpp>
#include <engine/scene/mesh.hpp>
#include <engine/core/timer.hpp>

#include <imgui.h>

#include <cmath>

using namespace engine;

class Application : public ApplicationContext {
public:
    auto Configure() -> void override{
        params.width = 1024;
        params.height = 768;
        params.antialiasing = 0;
    }

    auto Setup() -> void override {
        ApplicationContext::Setup();

        window->SetTitle("Examples");
        renderer->SetClearColor({0.0f, 0.0f, 0.5f, 1.0f});

        scene = Scene::Create();
        camera = CameraPerspective::Create(60.0f, window->AspectRatio());

        auto camera_controls = CameraOrbit::Create(camera);
        camera_controls->distance = 3.0f;

        scene->Add(camera_controls);

        auto geometry = BoxGeometry::Create({});
        auto material = PhongMaterial::Create();
        material->texture_map = Texture2D::Create("assets/checker.png");
        mesh_ = Mesh::Create(geometry, material);

        scene->Add(mesh_);

        auto ambient_light = AmbientLight::Create(0xffffff, 0.2f);
        scene->Add(ambient_light);

        auto directional_light = DirectionalLight::Create(0xffffff, 1.0f);
        directional_light->transform.Translate({2.0f, 2.0f, 0.0f});
        directional_light->SetDebugMode(true);
        scene->Add(directional_light);

        directional_light->target = mesh_;

        timer_.Start();
    }

    auto Update(float delta) -> bool override {
        ImGui::SetNextWindowSize(ImVec2(250, 748));
        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::Begin("Examples", nullptr,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoSavedSettings
        );

        ImGui::End();

        auto velocity = static_cast<float>(std::cos(timer_.GetElapsedSeconds()));
        mesh_->transform.Translate({0.0f, 0.0f, velocity * delta});

        return true;
    }

private:
    std::shared_ptr<Mesh> mesh_;

    Timer timer_;
};

auto main() -> int {
    auto app = Application {};
    app.Start();

    return 0;
}