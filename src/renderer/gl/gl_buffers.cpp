/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "renderer/gl/gl_buffers.hpp"

#include "utilities/logger.hpp"

#include <utility>

namespace gleam {

#define BUFFER_OFFSET(offset) ((void*)(offset * sizeof(GLfloat)))

auto GLBuffers::Bind(const std::shared_ptr<Geometry>& geometry) -> void {
    auto vao = geometry->renderer_id;
    if (vao != 0 && vao == current_vao_) return;

    if (vao == 0) {
        GenerateBuffers(geometry.get());
        vao = geometry->renderer_id;
        geometries_.emplace_back(geometry);
    }

    glBindVertexArray(vao);
    current_vao_ = vao;
}

auto GLBuffers::GenerateBuffers(Geometry* geometry) -> void {
    auto& vao = geometry->renderer_id;
    auto buffers = std::array<GLuint, 2> {};

    glGenVertexArrays(1, &vao);
    glBindVertexArray(geometry->renderer_id);
    glGenBuffers(buffers.size(), buffers.data());

    const auto& vertex = geometry->VertexData();
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
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
        auto idx = std::to_underlying(attr.type);
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
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            index.size() * sizeof(GLuint),
            index.data(),
            GL_STATIC_DRAW
        );
    }

    bindings_.try_emplace(vao, std::move(buffers));

    geometry->OnDispose([this](Disposable* target){
        const auto vao = static_cast<Geometry*>(target)->renderer_id;
        auto& buffers = this->bindings_[vao];
        glDeleteBuffers(buffers.size(), buffers.data());
        Logger::Log(LogLevel::Info, "Geometry buffer cleared {}", *static_cast<Geometry*>(target));
        this->bindings_.erase(vao);
    });
}

GLBuffers::~GLBuffers() {
    for (const auto& geometry : geometries_) {
        if (auto g = geometry.lock()) g->Dispose();
    }
}

}