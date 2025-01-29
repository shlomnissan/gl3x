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

        in vec3 a_Position;

        uniform mat4 u_ModelView;
        uniform mat4 u_Projection;

        void main() {
            gl_Position = u_ModelView * u_Projection * vec4(a_Position, 1.0);
        })",

        // ----------------
        // fragment shader
        // ----------------
        R"(#version 410 core
        #pragma inject_attributes

        precision mediump float;

        layout (location = 0) out vec4 v_FragColor;

        void main() {
            v_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        })"
    );

    auto plane_mesh = Mesh::Create(plane_geometry, opaque_material);
    Add(plane_mesh);
}

auto ExampleSandbox::Update(float delta) -> void {
    // TODO: implement.
}