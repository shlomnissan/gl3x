/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <vector>

#include <vglx/vglx.hpp>
#include <imgui/imgui.h>

#include "ui_helpers.hpp"
#include "example_scene.hpp"

#include "animation/example_animated_transform.hpp"
#include "lighting/example_directional_light.hpp"
#include "lighting/example_point_light.hpp"
#include "lighting/example_spot_light.hpp"
#include "materials/example_phong_material.hpp"
#include "materials/example_shader_material.hpp"
#include "materials/example_unlit_material.hpp"
#include "rendering_effects/example_blending.hpp"
#include "rendering_effects/example_fog.hpp"
#include "sandbox/example_sandbox.hpp"
#include "scene_features/example_debug_visuals.hpp"
#include "scene_features/example_frustum_culling.hpp"
#include "scene_features/example_mesh_instancing.hpp"
#include "scene_features/example_model_loader.hpp"
#include "scene_features/example_primitives.hpp"
#include "scene_features/example_sprite.hpp"

namespace {

    const auto examples = std::vector {
    "- Materials",
    "Unlit Material",
    "Phong Material",
    "Shader Material",
    "- Lights",
    "Directional Light",
    "Point Light",
    "Spot Light",
    "- Rendering Effects",
    "Transparency & Blending",
    "Fog Effect",
    "- Scene Features",
    "Frustum Culling",
    "Mesh Instancing",
    "Model Loader",
    "Primitives",
    "Sprite",
    "Debug Visuals",
    "- Animation",
    "Animated Transform"
};

}

using SceneChangeCallback = std::function<void(std::shared_ptr<gl3x::Scene>)>;

class Examples {
public:
    std::shared_ptr<ExampleScene> scene;

    Examples(SceneChangeCallback cb) : scene_change_cb_ {std::move(cb)} {
        Theme();
        LoadScene(examples[current_scene_]);
    }

    auto Draw() -> void {
        const auto height = ImGui::GetIO().DisplaySize.y;

        ImGui::SetNextWindowSize({250, height - 20.0f});
        ImGui::SetNextWindowPos({10, 10});
        ImGui::Begin("GL3X", nullptr,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove
        );

        if (ImGui::CollapsingHeader("Examples", ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::BeginListBox("##ListBox", {235, 384})) {
                for (auto i = 0; i < examples.size(); i++) {
                    const auto name = std::string_view {examples[i]};
                    if (name.starts_with("-")) {
                        UISeparator();
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4, 0.4, 0.4, 1));
                        ImGui::TextUnformatted(name.substr(2).data());
                        ImGui::PopStyleColor();
                        UISeparator();
                    } else if (
                        ImGui::Selectable(name.data(), current_scene_ == i)
                        && current_scene_ != i
                    ) {
                        current_scene_ = i;
                        LoadScene(name);
                    }
                }
                ImGui::EndListBox();
            }
        }

        if (scene->show_context_menu_) {
            if (ImGui::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
                scene->ContextMenu();
            }
        }

        ImGui::End();
    }

    auto LoadScene(const std::string_view scene_name) -> void {
        if (current_scene_ == 0) scene.reset(new ExampleSandbox());

        if (scene_name == "Unlit Material") scene.reset(new ExampleUnlitMaterial());
        if (scene_name == "Phong Material") scene.reset(new ExamplePhongMaterial());
        if (scene_name == "Shader Material") scene.reset(new ExampleShaderMaterial());
        if (scene_name == "Directional Light") scene.reset(new ExampleDirectionalLight());
        if (scene_name == "Point Light") scene.reset(new ExamplePointLight());
        if (scene_name == "Spot Light") scene.reset(new ExampleSpotLight());
        if (scene_name == "Transparency & Blending") scene.reset(new ExampleBlending());
        if (scene_name == "Fog Effect") scene.reset(new ExampleFog());
        if (scene_name == "Frustum Culling") scene.reset(new ExampleFrustumCulling());
        if (scene_name == "Mesh Instancing") scene.reset(new ExampleMeshInstancing());
        if (scene_name == "Model Loader") scene.reset(new ExampleModelLoader());
        if (scene_name == "Primitives") scene.reset(new ExamplePrimitives());
        if (scene_name == "Sprite") scene.reset(new ExampleSprite());
        if (scene_name == "Debug Visuals") scene.reset(new ExampleDebugVisuals());
        if (scene_name == "Animated Transform") scene.reset(new ExampleAnimatedTransform());

        scene_change_cb_(scene);
    }

private:
    SharedContextPointer context_ {nullptr};

    SceneChangeCallback scene_change_cb_;

    int current_scene_ = 0;
};