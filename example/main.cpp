// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <array>

#include "core/mesh.h"
#include "core/shader.h"

#include "shaders/headers/scene_vert.h"
#include "shaders/headers/scene_frag.h"

#include "mesh/cube.h"

#include <engine/core.hpp>
#include <engine/math.hpp>

auto main() -> int {
    const auto width = 800;
    const auto height = 600;

    auto window = engine::Window {"Example", 800, 600};
    auto timer = engine::Timer {};

    auto shader = Shader {{
        {ShaderType::kVertexShader, _SHADER_scene_vert},
        {ShaderType::kFragmentShader, _SHADER_scene_frag}
    }};

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glViewport(0, 0, window.width(), window.height());

    auto ratio = static_cast<float>(width) / static_cast<float>(height);
    shader.SetUniform("Projection", engine::perspective(45.0f, ratio, 0.1f, 100.0f));

    auto view = engine::look_at(
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f}
    );

    auto cube = Mesh {cube_vertex_0, cube_index_0};

    timer.Start();
    window.Start([&](const double _){
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto model = engine::Matrix4 {1.0f};
        model = engine::scale(model, 0.3f);
        model = engine::rotate(model, static_cast<float>(timer.GetElapsedSeconds()), {1.0f, 1.0f, 1.0f});
        shader.SetUniform("ModelView", view * model);

        cube.Draw(shader);
    });

    return 0;
}