// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/core/renderer.hpp"
#include "engine/scene/mesh.hpp"

#include "renderer/gl/gl_buffers.hpp"
#include "renderer/gl/gl_programs.hpp"
#include "renderer/gl/gl_textures.hpp"

namespace engine {

class Renderer::Impl {
public:
    Impl(const Renderer::Parameters& params);

    Impl(const Impl&) = delete;
    Impl(Impl&&) = delete;
    Impl& operator=(const Impl&) = delete;
    Impl& operator=(Impl&&) = delete;

    auto Render(Scene* scene, Camera* camera) -> void;

    auto SetClearColor(const Color& color) -> void { clear_color_ = color; }

private:
    GLBuffers buffers_;
    GLPrograms programs_;
    GLTextures textures_;

    Color clear_color_ {0.0f, 0.0f, 0.0f, 1.0f};

    bool curr_backface_culling {true};

    auto RenderObjects(const Node* object, Camera* camera) -> void;

    auto SetUniforms(GLProgram* program, const ProgramAttributes& attrs, Mesh* mesh, const Camera* camera) -> void;

    [[nodiscard]] auto IsValidMesh(Mesh* mesh) const -> bool;
};

}