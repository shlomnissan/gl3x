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
    bool fog_enabled = false;
    Color fog_color = 0x3f7b9d;
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

        window->SetTitle("Glide");
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
            if (ImGui::CollapsingHeader("Examples")) DrawExamplesList();
            if (ImGui::CollapsingHeader("Scene")) DrawSceneSettings();
        ImGui::End();

        return true;
    }

    auto DrawExamplesList() -> void {
        if (ImGui::BeginListBox("##ListBox", {250, 0})) {
            for (auto i = 0; i < examples.size(); i++) {
                const auto name = examples[i];
                if (name == "") {
                    ImGui::Separator();
                } else if (ImGui::Selectable(name, current_scene_ == i) && current_scene_ != i) {
                    current_scene_ = i;
                    LoadScene(name);
                }
            }
            ImGui::EndListBox();
        }
    }

    auto DrawSceneSettings() -> void {
        ImGui::Checkbox("Fog Enabled", &scene_settings_.fog_enabled);
        ImGui::ColorEdit3("Fog Color", &scene_settings_.fog_color[0]);
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