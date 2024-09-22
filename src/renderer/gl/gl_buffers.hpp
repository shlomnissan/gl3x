// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/core/geometry.hpp"

#include <array>
#include <string_view>
#include <unordered_map>

#include <glad/glad.h>

namespace engine {

struct GLBufferState {
    std::array<GLuint, 2> buffers {0};
    GLuint vao {0};
};

class GLBuffers {
public:
    GLBuffers() = default;

    GLBuffers(const GLBuffers&) = delete;
    GLBuffers(GLBuffers&&) = delete;
    GLBuffers& operator=(const GLBuffers&) = delete;
    GLBuffers& operator=(GLBuffers&&) = delete;

    auto Bind(Geometry* geometry) -> void;

private:
    std::unordered_map<std::string_view, GLBufferState> bindings_;

    GLuint current_vao_ {0};

    auto GenerateBuffers(const Geometry* geometry, GLBufferState& state) const -> void;

    auto GeometryCallbacks(Geometry* geometry) -> void;
};

}