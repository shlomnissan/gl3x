// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core/application_context.hpp>
#include <engine/geometry/box_geometry.hpp>
#include <engine/scene/camera_perspective.hpp>
#include <engine/scene/mesh.hpp>
#include <engine/core/timer.hpp>

#include <engine/math/utilities.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

#include <cmath>

#include <imgui.h>

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
        renderer->SetClearColor(0x5C5C5C);

        scene = Scene::Create();
        camera = CameraPerspective::Create(60.0f, window->AspectRatio());
        camera->transform.Translate({0.0f, 0.0f, 4.0f});

        const auto initial_orientation = Euler {{.pitch = math::DegToRad(25.0f), .yaw = math::DegToRad(-45.0f)}};
        const auto camera_controls = CameraOrbit::Create(camera, initial_orientation);
        scene->Add(camera_controls);

        auto grid = Grid::Create(20.0f);
        scene->Add(grid);

        auto geometry = BoxGeometry::Create({});
        auto material = PhongMaterial::Create();
        material->texture_map = Texture2D::Create("assets/checker.png");
        mesh_ = Mesh::Create(geometry, material);

        scene->Add(mesh_);

        auto ambient_light = AmbientLight::Create(0xffffff, 0.2f);
        scene->Add(ambient_light);

        auto directional_light = DirectionalLight::Create(0xffffff, 1.0f);
        directional_light->transform.Translate({2.0f, 2.0f, 2.0f});
        directional_light->SetDebugMode(true);
        scene->Add(directional_light);

        directional_light->target = mesh_;

        timer_.Start();
    }

    auto Update(float delta) -> bool override {
        ImGui::SetNextWindowSize({250, 748});
        ImGui::SetNextWindowPos({10, 10});
        ImGui::Begin("Examples", nullptr,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove
        );
            if (ImGui::BeginListBox("##ListBox", {234, 0})) {
                ImGui::Selectable("Flat Color");
                ImGui::Separator();
                ImGui::Selectable("Directional Light");
                ImGui::EndListBox();
            }

        ImGui::End();

        // auto velocity = static_cast<float>(std::cos(timer_.GetElapsedSeconds()));
        // mesh_->transform.Translate({0.0f, 0.0f, velocity * delta});

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