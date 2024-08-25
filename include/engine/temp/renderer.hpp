// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <glad/glad.h>
#include <iostream>

#include <engine/temp/shader.hpp>
#include <engine/temp/scene_vert.h>
#include <engine/temp/scene_frag.h>
#include <engine/temp/mesh.hpp>
#include <engine/temp/cube.h>

#include "engine/math/transformations.hpp"
#include "engine/math/projection.hpp"
#include "engine/math/matrix4.hpp"
#include "engine/scene/scene.hpp"

#include "scene/camera.hpp"

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
    }

    auto drawCube(const engine::Matrix4 transform) {
        shader_.SetUniform("ModelView", camera_ * transform);

        cube_.Draw(shader_);
    }

    auto renderObject(Node* object) -> void {
        for (const auto c : object->Children()) {
            drawCube(c->GetWorldTransform());
            renderObject(c.get());
        }
    }

    auto render(Scene& scene, Camera* camera) {
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.UpdateTransforms();

        shader_.Use();
        shader_.SetUniform("Projection", camera->GetProjectionMatrix());

        renderObject(&scene);
    }
};

}