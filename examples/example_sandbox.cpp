// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_sandbox.hpp"

#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleSandbox::ExampleSandbox(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 6.0f);
    Add(camera_controls);

    auto ambient = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient);

    auto directional_light = DirectionalLight::Create(0xFFFFFF, 1.0f);
    directional_light->transform.Translate({2.0f, 2.0f, 2.0f});
    directional_light->SetDebugMode(true);
    Add(directional_light);

    auto plane_geometry = PlaneGeometry::Create({3.0f, 3.0f});
    auto opaque_material = PhongMaterial::Create();
    opaque_material->color = 0xEF798A;

    auto shader_material = ShaderMaterial::Create(
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

    auto plane_mesh = Mesh::Create(plane_geometry, shader_material);
    Add(plane_mesh);
}

auto ExampleSandbox::Update(float delta) -> void {
    // TODO: implement.
}