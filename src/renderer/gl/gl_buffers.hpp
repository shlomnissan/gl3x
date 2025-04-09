// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine/core/geometry.hpp"

#include <array>
#include <memory>
#include <string_view>
#include <unordered_map>
#include <vector>

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

    auto Bind(const std::shared_ptr<Geometry>& geometry) -> void;

    ~GLBuffers();

private:
    std::unordered_map<std::string_view, GLBufferState> bindings_;

    std::vector<std::weak_ptr<Geometry>> geometries_;

    GLuint current_vao_ {0};

    auto GenerateBuffers(const Geometry* geometry, GLBufferState& state) const -> void;

    auto GeometryCallbacks(Geometry* geometry) -> void;
};

}