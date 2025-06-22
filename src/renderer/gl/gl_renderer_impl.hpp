/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/math/frustum.hpp"
#include "gleam/nodes/mesh.hpp"

#include "core/renderer.hpp"

#include "renderer/gl/gl_buffers.hpp"
#include "renderer/gl/gl_camera.hpp"
#include "renderer/gl/gl_lights.hpp"
#include "renderer/gl/gl_programs.hpp"
#include "renderer/gl/gl_state.hpp"
#include "renderer/gl/gl_textures.hpp"

#include <memory>

namespace gleam {

class RenderLists;

class Renderer::Impl {
public:
    explicit Impl(const Renderer::Parameters& params);

    Impl(const Impl&) = delete;
    Impl(Impl&&) = delete;
    Impl& operator=(const Impl&) = delete;
    Impl& operator=(Impl&&) = delete;

    auto Render(Scene* scene, Camera* camera) -> void;

    auto SetClearColor(const Color& color) -> void;

    [[nodiscard]] auto RenderedObjectsPerFrame() const {
        return rendered_objects_per_frame_;
    }

    ~Impl();

private:
    GLBuffers buffers_;
    GLCamera camera_;
    GLLights lights_;
    GLPrograms programs_;
    GLState state_;
    GLTextures textures_;

    Renderer::Parameters params_;

    Frustum frustum_;

    std::unique_ptr<RenderLists> render_lists_;

    size_t rendered_objects_counter_ {0};
    size_t rendered_objects_per_frame_ {0};

    auto RenderObjects(Scene* scene, Camera* camera) -> void;

    auto RenderMesh(Mesh* mesh, Scene* scene, Camera* camera) -> void;

    auto SetUniforms(
        GLProgram* program,
        ProgramAttributes* attrs,
        Mesh* mesh,
        Camera* camera,
        Scene* scene
    ) -> void;

    [[nodiscard]] auto IsValidMesh(Mesh* mesh) const -> bool;

    [[nodiscard]] auto IsVisible(Mesh* mesh) const -> bool;
};

}