// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine/core/renderer.hpp"
#include "engine/nodes/mesh.hpp"

#include "renderer/gl/gl_buffers.hpp"
#include "renderer/gl/gl_programs.hpp"
#include "renderer/gl/gl_state.hpp"
#include "renderer/gl/gl_textures.hpp"

namespace engine {

class Renderer::Impl {
public:
    explicit Impl(const Renderer::Parameters& params);

    Impl(const Impl&) = delete;
    Impl(Impl&&) = delete;
    Impl& operator=(const Impl&) = delete;
    Impl& operator=(Impl&&) = delete;

    auto Render(Scene* scene, Camera* camera) -> void;

    auto SetClearColor(const Color& color) -> void;

private:
    GLBuffers buffers_;
    GLPrograms programs_;
    GLState state_;
    GLTextures textures_;

    auto RenderObjects(Node* node, Scene* scene, Camera* camera) -> void;

    auto SetUniforms(
        GLProgram* program,
        ProgramAttributes* attrs,
        Mesh* mesh,
        Camera* camera,
        Scene* scene
    ) -> void;

    auto UpdateLights(const Scene* scene, GLProgram* program, const Camera* camera) const -> void;

    [[nodiscard]] auto IsValidMesh(Mesh* mesh) const -> bool;
};

}