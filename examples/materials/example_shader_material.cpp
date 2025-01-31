// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_shader_material.hpp"

#include <engine/geometries.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleShaderMaterial::ExampleShaderMaterial(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 3.0f);
    Add(camera_controls);

    auto geometry = BoxGeometry::Create();
    auto material = ShaderMaterial::Create(
        // ----------------
        // vertex shader
        // ----------------
        R"(#version 410 core
        #pragma inject_attributes

        #include "snippets/common_vert_params.glsl"

        void main() {
            #include "snippets/common_vert_varyings.glsl"

            gl_Position = u_Projection * v_Position;
        })",

        // ----------------
        // fragment shader
        // ----------------
        R"(#version 410 core
        #pragma inject_attributes

        precision mediump float;

        #include "snippets/common_frag_params.glsl"
        #include "snippets/fog.glsl"

        uniform vec3 u_ThisColor;

        void main() {
            v_FragColor = vec4(u_ThisColor, u_Opacity);

            #ifdef USE_FOG
                applyFog(v_FragColor, v_FogDepth);
            #endif
        })",

        // ----------------
        // uniforms
        // ----------------
        {
            {"u_ThisColor", Color(0x00FF00)}
        }
    );

    mesh_ = Mesh::Create(geometry, material);
    Add(mesh_);
}

auto ExampleShaderMaterial::Update(float delta) -> void {
    mesh_->transform.Rotate(Vector3::Up(), 1.0f * delta);
    mesh_->transform.Rotate(Vector3::Right(), 1.0f * delta);
}