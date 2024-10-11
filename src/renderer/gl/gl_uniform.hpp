// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/color.hpp"
#include "engine/math/matrix4.hpp"

#include <variant>

#include <glad/glad.h>

namespace engine {

using GLUniformValue = std::variant<int, Matrix4>;

struct GLUniform {
    GLint location {0};
    GLint size {0};
    GLenum type {0};
    GLUniformValue value {0};
    bool needs_update {false};
};

}