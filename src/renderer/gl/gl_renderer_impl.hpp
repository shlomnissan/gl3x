// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/core/renderer.hpp"

#include "renderer/gl/gl_buffers.hpp"
#include "renderer/gl/gl_program.hpp"
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

private:
    Renderer::Parameters params_;

    GLProgram program_;
    GLBuffers buffers_;
    GLTextures textures_;

    auto RenderObject(Node* object, Camera* camera) -> void;
};

}