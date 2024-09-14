// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/scene/mesh.hpp"

#include <string>
#include <unordered_map>

#include <glad/glad.h>

namespace engine {

class GLBindings {
public:
    GLBindings() = default;

    GLBindings(const GLBindings&) = delete;
    GLBindings(GLBindings&&) = delete;
    GLBindings& operator=(const GLBindings&) = delete;
    GLBindings& operator=(GLBindings&&) = delete;

    auto Bind(Geometry* geometry) -> void;

private:
    std::unordered_map<std::string, GLuint> vao_bindings_;

    GLuint current_vao_ {0};

    auto GenerateBuffers(Geometry* geometry) const -> void;
};

}