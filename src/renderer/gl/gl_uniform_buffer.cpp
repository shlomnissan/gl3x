/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "renderer/gl/gl_uniform_buffer.hpp"

#include "utilities/logger.hpp"

namespace gleam {

GLUniformBuffer::GLUniformBuffer(std::string_view name, std::size_t size) :
    name_(name),
    binding_point_(get_uniform_block_loc(name)),
    size_(size)
{
    glGenBuffers(1, &buffer_);
    glBindBuffer(GL_UNIFORM_BUFFER, buffer_);
    glBufferData(GL_UNIFORM_BUFFER, size_, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_point_, buffer_);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

auto GLUniformBuffer::UploadIfNeeded(const void* data, std::size_t size) const -> void {
    if (size > size_) {
        Logger::Log(LogLevel::Error, "UBO {} update size exceeds buffer size", name_);
        return;
    }
    glBindBuffer(GL_UNIFORM_BUFFER, buffer_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GLUniformBuffer::~GLUniformBuffer() {
    if (buffer_ != 0) {
        glDeleteBuffers(1, &buffer_);
        buffer_ = 0;
    }
}

}