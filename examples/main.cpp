// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <memory>
#include <string_view>

#include <engine/core.hpp>
#include <engine/resources.hpp>
#include <engine/math.hpp>
#include <imgui.h>

#include "examples.hpp"

using namespace engine;

struct SceneSettings {
    Color fog_color = 0x3f7b9d;
    float fog_near = 1.0f;
    float fog_far = 1000.0f;
    bool fog_enabled = false;
};

class Application : public ApplicationContext {
public:
    auto Configure() -> void override {
        params.vsync = false;
        params.width = 1536;
        params.height = 1152;
        params.antialiasing = 0;
    }

    auto Setup() -> void override {
        ApplicationContext::Setup();

        window->SetTitle("Glide Engine");
        renderer->SetClearColor(0x444444);

        camera = CameraPerspective::Create(60.0f, window->AspectRatio());
        camera->transform.Translate({0.0f, 0.0f, 3.0f});

        LoadScene(examples[current_scene_]);
    }

    auto Update(float delta) -> bool override {
        const auto height = static_cast<float>(params.height) - 20.0f;
        ImGui::SetNextWindowSize({250, height - 20.0f});
        ImGui::SetNextWindowPos({10, 10});
        ImGui::Begin("Glide Engine", nullptr,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove
        );
            DrawPerformance();
            ImGui::Separator();
            if (ImGui::CollapsingHeader("Examples")) DrawExamplesList();
            if (ImGui::CollapsingHeader("Scene")) DrawSceneSettings();
        ImGui::End();

        return true;
    }

    auto DrawPerformance() -> void {
        ImGui::Text("FPS: %.2f", frames_per_second_.LastValue());
        ImGui::PlotHistogram(
            "##Frames Per Second",
            frames_per_second_.Buffer(), 150, 0, nullptr, 0.0f, 120.0f, {235, 40}
        );
    }

    auto DrawExamplesList() -> void {
        if (ImGui::BeginListBox("##ListBox", {235, 0})) {
            for (auto i = 0; i < examples.size(); i++) {
                const auto name = std::string_view {examples[i]};
                if (name.empty()) {
                    ImGui::Separator();
                } else if (ImGui::Selectable(name.data(), current_scene_ == i) && current_scene_ != i) {
                    current_scene_ = i;
                    LoadScene(name);
                }
            }
            ImGui::EndListBox();
        }
    }

    auto DrawSceneSettings() -> void {
        float near = 1.0f;
        float far = 1000.0f;
        ImGui::Checkbox("Fog Enabled", &scene_settings_.fog_enabled);
        if (scene_settings_.fog_enabled) {
            ImGui::ColorEdit3("Fog Color", &scene_settings_.fog_color[0]);

            const auto AddSlider = [](std::string_view label, float* val) {
                ImGui::Text(label.data());
                ImGui::SameLine();
                ImGui::PushItemWidth(200.0f);
                ImGui::SliderFloat(fmt::format("##{}", label).c_str(), val, 0.0f, 1500.0f);
                ImGui::PopItemWidth();
            };

            AddSlider("Near", &scene_settings_.fog_near);
            AddSlider("Far ", &scene_settings_.fog_far);
        }
    }

private:
    SceneSettings scene_settings_;

    int current_scene_ = 0;

    auto LoadScene(const std::string_view scene_name) -> void {
        if (scene_name == "Flat Material") {
            scene = std::make_shared<ExampleMaterialsFlat>(camera);
        }
        if (scene_name == "Phong Material") {
            scene = std::make_shared<ExampleMaterialsPhong>(camera);
        }
        if (scene_name == "Directional Light") {
            scene = std::make_shared<ExampleLightsDirectional>(camera);
        }
        if (scene_name == "Point Light") {
            scene = std::make_shared<ExampleLightsPoint>(camera);
        }
    }
};

auto main() -> int {
    auto app = Application {};
    app.Start();

    return 0;
}