// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/scene/mesh.hpp"

#include <array>
#include <string>
#include <unordered_map>

#include <glad/glad.h>

namespace engine {

struct GLBindingsState {
    std::array<GLuint, 2> buffers {0};
    GLuint vao {0};
};

class GLBindings {
public:
    GLBindings() = default;

    GLBindings(const GLBindings&) = delete;
    GLBindings(GLBindings&&) = delete;
    GLBindings& operator=(const GLBindings&) = delete;
    GLBindings& operator=(GLBindings&&) = delete;

    auto Bind(Geometry* geometry) -> void;

private:
    std::unordered_map<std::string, GLBindingsState> bindings_;

    GLuint current_vao_ {0};

    auto GenerateBuffers(const Geometry* geometry, GLBindingsState& state) const -> void;

    auto GeometryCallbacks(Geometry* geometry) -> void;
};

}