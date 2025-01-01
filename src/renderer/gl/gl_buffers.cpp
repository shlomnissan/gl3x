// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "renderer/gl/gl_buffers.hpp"

#include "utilities/logger.hpp"

namespace engine {

#define BUFFER_OFFSET(offset) ((void*)(offset * sizeof(GLfloat)))

auto GLBuffers::Bind(Geometry* geometry) -> void {
    GLBufferState state;
    if (bindings_.contains(geometry->UUID())) {
        state = bindings_[geometry->UUID()];
        if (state.vao == current_vao_) { return; }
    } else {
        GenerateBuffers(geometry, state);
        GeometryCallbacks(geometry);
        bindings_.try_emplace(geometry->UUID(), state);
    }
    glBindVertexArray(state.vao);
    current_vao_ = state.vao;
}

auto GLBuffers::GenerateBuffers(const Geometry* geometry, GLBufferState& state) const -> void {
    glGenVertexArrays(1, &state.vao);
    glBindVertexArray(state.vao);
    glGenBuffers(state.buffers.size(), state.buffers.data());

    const auto& vertex = geometry->VertexData();
    glBindBuffer(GL_ARRAY_BUFFER, state.buffers[0]);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertex.size() * sizeof(GLfloat),
        vertex.data(),
        GL_STATIC_DRAW
    );

    auto offset = 0;
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
            BUFFER_OFFSET(offset)
        );
        glEnableVertexAttribArray(idx);
        offset += attr.item_size;
    }

    if (geometry->IndexData().size()) {
        const auto& index = geometry->IndexData();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state.buffers[1]);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            index.size() * sizeof(GLuint),
            index.data(),
            GL_STATIC_DRAW
        );
    }

    glBindVertexArray(0);
}

auto GLBuffers::GeometryCallbacks(Geometry* geometry) -> void {
    geometry->OnDispose([this](Disposable* target){
        Logger::Log(LogLevel::Info, "Geometry buffer cleared {}", *static_cast<Geometry*>(target));
        auto& uuid = static_cast<Geometry*>(target)->UUID();
        auto& state = this->bindings_[uuid];
        glDeleteBuffers(state.buffers.size(), state.buffers.data());
        this->bindings_.erase(uuid);
    });
}

}