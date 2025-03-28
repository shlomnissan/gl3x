// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_shader_material.hpp"

#include "ui_helpers.hpp"

#include <engine/geometries.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleShaderMaterial::ExampleShaderMaterial(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 3.0f);
    Add(camera_controls);

    auto geometry = BoxGeometry::Create();

    material_ = ShaderMaterial::Create(
        // Vertex shader
        R"(#version 410 core
        #pragma inject_attributes

        #include "snippets/vert_global_params.glsl"

        void main() {
            #include "snippets/vert_main_varyings.glsl"

            gl_Position = u_Projection * v_Position;
        })",

        // Fragment shader
        R"(#version 410 core
        #pragma inject_attributes

        precision mediump float;

        #include "snippets/frag_global_params.glsl"
        #include "snippets/frag_global_fog.glsl"

        uniform float u_Time;
        uniform vec2 u_Resolution;

        void main() {
            vec2 uv = gl_FragCoord.xy / u_Resolution.xy;
            vec3 col = 0.5 + 0.5 * cos(u_Time + uv.xyx + vec3(0,2,4));
            v_FragColor = vec4(col, u_Opacity);
            #ifdef USE_FOG
                applyFog(v_FragColor, v_ViewDepth);
            #endif
        })",

        // Uniforms
        {{"u_Time", 0.0f}}
    );

    mesh_ = Mesh::Create(geometry, material_);
    Add(mesh_);
}

auto ExampleShaderMaterial::Update(float delta) -> void {
    mesh_->transform.Rotate(Vector3::Up(), 1.0f * delta);
    mesh_->transform.Rotate(Vector3::Right(), 1.0f * delta);
    material_->uniforms["u_Time"] = static_cast<float>(timer_.GetElapsedSeconds());
}

auto ExampleShaderMaterial::ContextMenu() -> void {
    static bool _ = false;

    UICheckbox("two_sided", material_->two_sided, _);
    UICheckbox("transparent", material_->transparent, _);
    UISliderFloat("opacity", material_->opacity, 0.0f, 1.0f, _);
}