/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <memory>
#include <string_view>

#include <gleam/core.hpp>
#include <gleam/math.hpp>

#include "ui_helpers.hpp"

#include "example_scene.hpp"
#include "examples.hpp"

#include <imgui/imgui.h>

using namespace gleam;

class Application : public ApplicationContext {
public:
    auto Configure() -> void override {
        params.width = 1024;
        params.height = 768;
        params.antialiasing = 0;
        params.vsync = false;
        params.debug = true;
        params.title = "Gleam Engine";
        params.clear_color = 0x444444;
    }

    auto CreateScene() -> std::shared_ptr<Scene> override {
        Theme();

        LoadScene(examples[current_scene_]);
        return scene_;
    }

    auto CreateCamera() -> std::shared_ptr<Camera> override {
        camera_ = PerspectiveCamera::Create({
            .fov = math::DegToRad(60.0f),
            .aspect = params.Ratio(),
            .near = 0.1f,
            .far = 1000.0f
        });
        camera_->transform.Translate({0.0f, 0.0f, 3.0f});
        return camera_;
    }

    auto Update(float delta) -> bool override {
        const auto height = static_cast<float>(params.height);
        ImGui::SetNextWindowSize({250, height - 20.0f});
        ImGui::SetNextWindowPos({10, 10});
        ImGui::Begin("Gleam Engine", nullptr,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove
        );
        if (ImGui::CollapsingHeader("Examples", ImGuiTreeNodeFlags_DefaultOpen)) {
            DrawExamplesList();
        }

        if (scene_->show_context_menu_) {
            if (ImGui::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
                scene_->ContextMenu();
            }
        }

        ImGui::End();
        return true;
    }

    auto DrawExamplesList() -> void {
        if (ImGui::BeginListBox("##ListBox", {235, 384})) {
            for (auto i = 0; i < examples.size(); i++) {
                const auto name = std::string_view {examples[i]};
                if (name.starts_with("-")) {
                    UISeparator();
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4, 0.4, 0.4, 1));
                    ImGui::TextUnformatted(name.substr(2).data());
                    ImGui::PopStyleColor();
                    UISeparator();
                } else if (ImGui::Selectable(name.data(), current_scene_ == i) && current_scene_ != i) {
                    current_scene_ = i;
                    LoadScene(name);
                }
            }
            ImGui::EndListBox();
        }
    }

private:
    std::shared_ptr<PerspectiveCamera> camera_;
    std::shared_ptr<ExampleScene> scene_;

    int current_scene_ = 1;

    auto LoadScene(const std::string_view scene_name) -> void {
        if (current_scene_ == 0) {
            scene_ = std::make_shared<ExampleSandbox>();
        }

        // materials
        if (scene_name == "Unlit Material") {
            scene_ = std::make_shared<ExampleUnlitMaterial>();
        }
        if (scene_name == "Phong Material") {
            scene_ = std::make_shared<ExamplePhongMaterial>();
        }
        if (scene_name == "Shader Material") {
            scene_ = std::make_shared<ExampleShaderMaterial>();
        }

        // lighting
        if (scene_name == "Directional Light") {
            scene_ = std::make_shared<ExampleDirectionalLight>();
        }
        if (scene_name == "Point Light") {
            scene_ = std::make_shared<ExamplePointLight>();
        }
        if (scene_name == "Spot Light") {
            scene_ = std::make_shared<ExampleSpotLight>();
        }

        // rendering effects
        if (scene_name == "Transparency & Blending") {
            scene_ = std::make_shared<ExampleBlending>();
        }
        if (scene_name == "Fog Effect") {
            scene_ = std::make_shared<ExampleFog>();
        }

        // scene features
        if (scene_name == "Frustum Culling") {
            scene_ = std::make_shared<ExampleFrustumCulling>();
        }
        if (scene_name == "Mesh Instancing") {
            scene_ = std::make_shared<ExampleMeshInstancing>();
        }
        if (scene_name == "Model Loader") {
            scene_ = std::make_shared<ExampleModelLoader>();
        }
        if (scene_name == "Primitives") {
            scene_ = std::make_shared<ExamplePrimitives>();
        }
        if (scene_name == "Sprite") {
            scene_ = std::make_shared<ExampleSprite>();
        }
        if (scene_name == "Debug Visuals") {
            scene_ = std::make_shared<ExampleDebugVisuals>();
        }

        // animation
        if (scene_name == "Animated Transform") {
            scene_ = std::make_shared<ExampleAnimatedTransform>();
        }

        SetScene(scene_);
    }
};

auto main() -> int {
    auto app = Application {};
    app.Start();

    return 0;
}