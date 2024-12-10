// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core.hpp>
#include <engine/resources.hpp>

#include "examples.hpp"

#include <imgui.h>

#include <memory>
#include <string>
#include <string_view>

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

        window->SetTitle("Glide3 Engine Examples");
        renderer->SetClearColor(0x000080);

        camera = CameraPerspective::Create(60.0f, window->AspectRatio());
        camera->transform.Translate({0.0f, 0.0f, 3.0f});

        LoadScene(examples.front());
    }

    auto Update(float delta) -> bool override {
        ImGui::SetNextWindowSize({250, 748});
        ImGui::SetNextWindowPos({10, 10});
        ImGui::Begin("Examples", nullptr,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove
        );
            if (ImGui::BeginListBox("##ListBox", {234, 188})) {
                for (auto i = 0; i < examples.size(); i++) {
                    if (ImGui::Selectable(examples[i], current_scene_ == i) && current_scene_ != i) {
                        current_scene_ = i;
                        LoadScene(examples[i]);
                    }
                }
                ImGui::EndListBox();
            }
        ImGui::End();
        return true;
    }

private:
    int current_scene_ = 0;

    auto LoadScene(const std::string_view scene_name) -> void {
        if (scene_name == "Flat Material") {
            scene = std::make_shared<ExampleFlatMaterial>(camera);
        }
        if (scene_name == "Phong Material") {
            scene = std::make_shared<ExamplePhongMaterial>(camera);
        }
    }
};

auto main() -> int {
    auto app = Application {};
    app.Start();

    return 0;
}