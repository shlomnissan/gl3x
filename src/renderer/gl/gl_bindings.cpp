// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_bindings.hpp"

namespace engine {

#define BUFFER_OFFSET(offset) ((void*)(offset * sizeof(GLfloat)))
#define STRIDE(stride) (sizeof(GLfloat) * stride)

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
    GLuint vbo;
    const auto& vertex = geometry->VertexData();

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertex.size() * sizeof(GLfloat),
        vertex.data(),
        GL_STATIC_DRAW
    );

    for (const auto& attr : geometry->Attributes()) {
        // TODO: process the rest of the attributes
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            STRIDE(8),
            BUFFER_OFFSET(0)
        );
        glEnableVertexAttribArray(0);
        break;
    }

    if (geometry->IndexData().size()) {
        // TODO: generate two buffers once
        GLuint ebo;
        const auto& index = geometry->IndexData();

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            index.size() * sizeof(GLuint),
            index.data(),
            GL_STATIC_DRAW
        );
    }
}

}