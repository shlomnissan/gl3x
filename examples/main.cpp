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

#include <imgui.h>

using namespace engine;

class Application : public ApplicationContext {
public:
    auto Configure() -> void override{
        params.width = 1024;
        params.height = 768;
        params.vsync = false;
    }

    auto Setup() -> void override {
        ApplicationContext::Setup();

        window->SetTitle("Examples");
        renderer->SetClearColor({0.0f, 0.0f, 0.5f, 1.0f});

        scene = Scene::Create();
        camera = CameraPerspective::Create(60.0f, window->AspectRatio());

        auto camera_controls = CameraOrbit::Create(camera);
        camera_controls->distance = 2.0f;

        scene->Add(camera_controls);

        auto ambient_light = AmbientLight::Create(0xffffff, 0.2f);
        scene->Add(ambient_light);

        auto directional_light = DirectionalLight::Create(0xffffff, 1.0f);
        directional_light->transform.Translate({2.0f, 2.0f, 2.0f});
        directional_light->SetDebugMode(true);
        scene->Add(directional_light);

        auto geometry = BoxGeometry::Create({});
        auto material = PhongMaterial::Create();
        material->texture_map = Texture2D::Create("assets/checker.png");
        mesh_ = Mesh::Create(geometry, material);
        mesh_->transform.Scale(0.7f);
        mesh_->transform.Rotate(Vector3::Up(), 15.0f);

        scene->Add(mesh_);
    }

    auto Update(float delta) -> bool override {
        ImGui::Begin("Examples");
        ImGui::End();

        // TODO: application logic

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