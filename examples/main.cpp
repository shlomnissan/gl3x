// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <memory>
#include <string_view>

#include <engine/core.hpp>
#include <engine/resources.hpp>
#include <engine/math.hpp>

#include <fmt/format.h>
#include <imgui.h>

#include "examples.hpp"

using namespace engine;

struct SceneSettings {
    bool fog_enabled = false;
};

class Application : public ApplicationContext {
public:
    auto Configure() -> void override {
        params.width = 1536;
        params.height = 1152;
        params.antialiasing = 0;
        params.vsync = false;
        params.debug = true;
    }

    auto Setup() -> void override {
        ApplicationContext::Setup();

        window->SetTitle("Build Engine");
        renderer->SetClearColor(0x444444);

        camera = CameraPerspective::Create({.aspect = window->AspectRatio()});
        camera->transform.Translate({0.0f, 0.0f, 3.0f});

        LoadScene(examples[current_scene_]);
    }

    auto Update(float delta) -> bool override {
        const auto height = static_cast<float>(params.height);
        ImGui::SetNextWindowSize({250, height - 20.0f});
        ImGui::SetNextWindowPos({10, 10});
        ImGui::SetNextWindowFocus();
        ImGui::Begin("Build Engine", nullptr,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove
        );
        if (ImGui::CollapsingHeader("Examples", ImGuiTreeNodeFlags_DefaultOpen)) DrawExamplesList();
        if (ImGui::CollapsingHeader("Scene")) DrawSceneSettings();
        ImGui::End();
        return true;
    }

    auto DrawExamplesList() -> void {
        if (ImGui::BeginListBox("##ListBox", {235, 200})) {
            for (auto i = 0; i < examples.size(); i++) {
                const auto name = std::string_view {examples[i]};
                if (name.empty()) {
                    ImGui::Separator();
                } else if (ImGui::Selectable(name.data(), current_scene_ == i) && current_scene_ != i) {
                    current_scene_ = i;
                    scene_settings_.fog_enabled = false;
                    LoadScene(name);
                }
            }
            ImGui::EndListBox();
        }
    }

    auto DrawSceneSettings() -> void {
        ImGui::Checkbox("Fog Enabled", &scene_settings_.fog_enabled);
        if (scene_settings_.fog_enabled) {
            if (!scene->fog.has_value()) {
                scene->fog = Scene::Fog {
                    .color = 0x3f7b9d,
                    .near = 1.0f,
                    .far = 5.0f
                };
            }

            const auto AddSlider = [](std::string_view label, float* val) {
                ImGui::Text("%s", label.data());
                ImGui::SameLine();
                ImGui::PushItemWidth(200.0f);
                ImGui::SliderFloat(fmt::format("##{}", label).c_str(), val, 0.0f, 50.0f);
                ImGui::PopItemWidth();
            };

            ImGui::ColorEdit3("Fog Color", &(scene->fog.value().color[0]));
            AddSlider("Near", &scene->fog.value().near);
            AddSlider("Far ", &scene->fog.value().far);
        } else {
            scene->fog.reset();
        }
    }

private:
    SceneSettings scene_settings_;

    int current_scene_ = 0;

    auto LoadScene(const std::string_view scene_name) -> void {
        if (scene_name == "Flat Material") {
            scene = std::make_shared<ExampleFlatMaterial>(camera);
        }
        if (scene_name == "Phong Material") {
            scene = std::make_shared<ExamplePhongMaterial>(camera);
        }
        if (scene_name == "Directional Light") {
            scene = std::make_shared<ExampleDirectionalLight>(camera);
        }
        if (scene_name == "Point Light") {
            scene = std::make_shared<ExamplePointLight>(camera);
        }
        if (scene_name == "Spot Light") {
            scene = std::make_shared<ExampleSpotLight>(camera);
        }
        if (scene_name == "Box Geometry") {
            scene = std::make_shared<ExampleBoxGeometry>(camera);
        }
        if (scene_name == "Cylinder Geometry") {
            scene = std::make_shared<ExampleCylinderGeometry>(camera);
        }
        if (scene_name == "Plane Geometry") {
            scene = std::make_shared<ExamplePlaneGeometry>(camera);
        }
        if (scene_name == "Sphere Geometry") {
            scene = std::make_shared<ExampleSphereGeometry>(camera);
        }
    }
};

auto main() -> int {
    auto app = Application {};
    app.Start();

    return 0;
}