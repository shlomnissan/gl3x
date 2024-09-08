// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_bindings.hpp"

namespace engine {

auto GLBindings::Bind(Mesh* mesh) -> void {
    GLuint vao;
    if (vao_bindings_.contains(mesh->UUID())) {
        vao = vao_bindings_[mesh->UUID()];
        if (vao == current_vao_) { return; }
        glBindVertexArray(vao);
    } else {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        GenerateBuffers(mesh->GetGeometry());
        vao_bindings_.emplace(mesh->UUID(), vao);
    }
    current_vao_ = vao;
}

auto GLBindings::GenerateBuffers(const Geometry* geometry) -> void {
    // TODO: implement
}

}