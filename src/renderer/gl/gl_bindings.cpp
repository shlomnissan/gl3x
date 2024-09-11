// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_bindings.hpp"

namespace engine {

#define BUFFER_OFFSET(offset) ((void*)(offset * sizeof(GLfloat)))

auto GLBindings::Bind(Mesh* mesh) -> void {
    GLuint vao;
    if (vao_bindings_.contains(mesh->UUID())) {
        vao = vao_bindings_[mesh->UUID()];
        if (vao == current_vao_) { return; }
    } else {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        GenerateBuffers(mesh->GetGeometry());
        vao_bindings_.emplace(mesh->UUID(), vao);
    }
    glBindVertexArray(vao);
    current_vao_ = vao;
}

auto GLBindings::GenerateBuffers(const Geometry* geometry) -> void {
    GLuint buffers[2];
    glGenBuffers(2, &buffers[0]);

    const auto& vertex = geometry->VertexData();
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertex.size() * sizeof(GLfloat),
        vertex.data(),
        GL_STATIC_DRAW
    );

    auto stride = 0;
    for (const auto& attr : geometry->Attributes()) {
        stride += attr.item_size;
    }

    for (const auto& attr : geometry->Attributes()) {
        auto idx = static_cast<int>(attr.type);
        glVertexAttribPointer(
            idx,
            attr.item_size,
            GL_FLOAT,
            GL_FALSE,
            stride * sizeof(GLfloat),
            BUFFER_OFFSET(0)
        );
        glEnableVertexAttribArray(idx);
    }

    if (geometry->IndexData().size()) {
        const auto& index = geometry->IndexData();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            index.size() * sizeof(GLuint),
            index.data(),
            GL_STATIC_DRAW
        );
    }

    glBindVertexArray(0);
}

}