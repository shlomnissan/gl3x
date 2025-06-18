/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <cstddef>
#include <span>
#include <string_view>

#include <glad/glad.h>

namespace gleam {

enum class UniformBuffer {
    Camera,
    Lights,
    KnownUniformBuffersLength
};

constexpr auto get_uniform_block_loc(std::string_view str) {
    using enum UniformBuffer;
    if (str == "ubo_Camera") return static_cast<int>(Camera);
    if (str == "ubo_Lights") return static_cast<int>(Lights);
    return -1;
}

class GLUniformBuffer {
public:
    GLUniformBuffer(std::string_view name, std::size_t size);

    auto UploadIfNeeded(const std::span<void*> data) const -> void;

    ~GLUniformBuffer();

private:
    GLuint buffer_ = 0;
    GLuint binding_point_ = 0;
    std::size_t size_ = 0;
};

}