// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <glad/glad.h>

#include <engine/math.hpp>
#include <engine/temp/shader.hpp>
#include <engine/temp/scene_vert.h>
#include <engine/temp/scene_frag.h>
#include <engine/temp/mesh.hpp>
#include <engine/temp/cube.h>

namespace engine {

struct ENGINE_EXPORT Renderer {
    Matrix4 camera_ = engine::look_at(
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f}
    );

    Shader shader_ {{
        {ShaderType::kVertexShader, _SHADER_scene_vert},
        {ShaderType::kFragmentShader, _SHADER_scene_frag}
    }};

    Mesh cube_ {cube_vertex_0, cube_index_0};

    Renderer(const int width, const int height) {
        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, width, height);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        auto ratio = static_cast<float>(width) / static_cast<float>(height);
        shader_.SetUniform("Projection", engine::perspective(45.0f, ratio, 0.1f, 100.0f));
    }

    auto render() {
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TODO: iterate through the scene
        // TODO: draw a cube for each node and apply transformations

        auto model = engine::Matrix4 {1.0f};
        model = engine::scale(model, 0.3f);
        shader_.SetUniform("ModelView", camera_ * model);

        cube_.Draw(shader_);
    }
};

}