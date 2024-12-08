// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core/application_context.hpp>
#include <engine/scene/camera_perspective.hpp>
#include <engine/scene/mesh.hpp>

#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

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
        renderer->SetClearColor(0x000080);

        scene = Scene::Create();
        camera = CameraPerspective::Create(60.0f, window->AspectRatio());
        camera->transform.Translate({0.0f, 0.0f, 3.0f});

        const auto camera_controls = CameraOrbit::Create(camera);
        scene->Add(camera_controls);

        auto geometry = CylinderGeometry::Create({});
        auto material = PhongMaterial::Create();
        material->color = 0x47A8BD;
        material->cull_backfaces = false;
        mesh_ = Mesh::Create(geometry, material);

        scene->Add(mesh_);

        auto point_light = PointLight::Create(0xf00ff0, 1.0f);
        point_light->transform.Translate({3.0f, 3.0f, 3.0f});
        point_light->SetDebugMode(true);
        scene->Add(point_light);
    }

    auto Update(float delta) -> bool override {
        ImGui::SetNextWindowSize({250, 748});
        ImGui::SetNextWindowPos({10, 10});
        ImGui::Begin("Examples", nullptr,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove
        );
            if (ImGui::BeginListBox("##ListBox", {234, 188})) {
                ImGui::Selectable("Flat Material");
                ImGui::Selectable("Phong Material");
                ImGui::Separator();
                ImGui::Selectable("Plane Geometry");
                ImGui::Selectable("Box Geometry");
                ImGui::Selectable("Cylinder Geometry");
                ImGui::Separator();
                ImGui::Selectable("Directional Light");
                ImGui::Selectable("Point Light");
                ImGui::Separator();
                ImGui::Selectable("2D Texture");
                ImGui::Separator();
                ImGui::Selectable("Orbit Camera");
                ImGui::Selectable("Grid");
                ImGui::EndListBox();
            }

        ImGui::End();
        mesh_->transform.Rotate(Vector3::Up(), 0.007f);

        return true;
    }

private:
    std::shared_ptr<Mesh> mesh_;
};

auto main() -> int {
    auto app = Application {};
    app.Start();

    return 0;
}