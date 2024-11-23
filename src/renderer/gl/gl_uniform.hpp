// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/core/logger.hpp"
#include "engine/math/color.hpp"
#include "engine/math/matrix3.hpp"
#include "engine/math/matrix4.hpp"
#include "engine/math/vector4.hpp"

#include <string>
#include <variant>

#include <glad/glad.h>

namespace engine {

using GLUniformValue = std::variant<GLint, GLfloat, Color, Matrix3, Matrix4, Vector3, Vector4>;

class GLUniform {
public:
    GLUniform(const std::string& name, GLint location, GLint size, GLenum type);

    auto SetValueIfNeeded(const GLUniformValue& v) -> void;

    auto UpdateUniformIfNeeded() -> void;

    const auto& Value() const { return value_; }

private:
    std::string name_ {};
    GLUniformValue value_ {};
    GLint location_ {0};
    GLint size_ {0};
    GLenum type_ {0};

    bool needs_update_ {true};

    template <typename... T>
    auto SetValue(const GLUniformValue& v) -> bool {
        return ((SetValueHelper<T>(v)) || ...);
    }

    template <typename T>
    auto SetValueHelper(const GLUniformValue& v) -> bool {
        if (const auto* f = std::get_if<T>(&v)) {
            value_ = *f;
            return true;
        }
        return false;
    }

    auto GLenumToString(GLenum type) const -> const char*;
};

}