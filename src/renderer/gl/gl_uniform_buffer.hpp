/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <memory>
#include <span>
#include <string>
#include <string_view>

#include <glad/glad.h>

namespace gl3x {

enum class UniformBuffer {
    Camera,
    Lights,
    KnownUniformBuffersLength
};

constexpr auto get_uniform_block_loc(std::string_view str) {
    using enum UniformBuffer;
    if (str == "ub_Camera") return static_cast<int>(Camera);
    if (str == "ub_Lights") return static_cast<int>(Lights);
    return -1;
}

class GLUniformBuffer {
public:
    GLUniformBuffer(std::string_view name, std::size_t size);

    // implement move constructor and assignment operator
    GLUniformBuffer(GLUniformBuffer&& other) noexcept;
    auto operator=(GLUniformBuffer&& other) noexcept -> GLUniformBuffer&;

    // delete copy constructor and assignment operator
    GLUniformBuffer(const GLUniformBuffer&) = delete;
    auto operator=(const GLUniformBuffer&) -> GLUniformBuffer& = delete;

    auto UploadIfNeeded(const void* data, std::size_t size) const -> void;

    ~GLUniformBuffer();

private:
    std::string name_ {""};
    GLuint buffer_ {0};
    int binding_point_ {-1};
    std::size_t size_ {0};
    std::unique_ptr<std::byte[]> data_;
};

}