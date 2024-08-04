// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/mesh.h"
#include "core/shader.h"
#include "core/window.h"

#include "shaders/headers/scene_vert.h"
#include "shaders/headers/scene_frag.h"

#include "mesh/cube.h"

#include <engine/math/vec3.hpp>

auto main() -> int {
    const auto width = 800;
    const auto height = 600;
    auto window = Window {width, height, "Tetris 3D"};

    auto shader = Shader {{
        {ShaderType::kVertexShader, _SHADER_scene_vert},
        {ShaderType::kFragmentShader, _SHADER_scene_frag}
    }};

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    auto updateProjection = [&shader](int width, int height) {
        auto ratio = static_cast<float>(width) / static_cast<float>(height);
        shader.SetUniform("Projection", glm::perspective(45.0f, ratio, 0.1f, 100.0f));
    };

    updateProjection(width, height);
    window.on_resize([&updateProjection](const int width, const int height){
        updateProjection(width, height);
    });

    auto view = glm::lookAt(
        glm::vec3{0.0f, 0.0f, 1.0f},
        glm::vec3{0.0f, 0.0f, 0.0f},
        glm::vec3{0.0f, 1.0f, 0.0f}
    );

    auto cube = Mesh {cube_vertex_0, cube_index_0};

    window.Start([&](const double delta){
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto model = glm::mat4{1.0f};
        model = glm::scale(model, {0.3f, 0.3f, 0.3f});
        model = glm::rotate(model, static_cast<float>(glfwGetTime()), {1.0f, 1.0f, 1.0f});
        shader.SetUniform("ModelView", view * model);

        cube.Draw(shader);
    });

    return 0;
}