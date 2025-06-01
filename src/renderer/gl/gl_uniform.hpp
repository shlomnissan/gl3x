// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam/math/color.hpp"
#include "gleam/math/matrix3.hpp"
#include "gleam/math/matrix4.hpp"
#include "gleam/math/vector2.hpp"
#include "gleam/math/vector3.hpp"
#include "gleam/math/vector4.hpp"


#include "utilities/logger.hpp"

#include <string>
#include <variant>

#include <glad/glad.h>

namespace gleam {

// UniformValue is also defined in include/gleam/materials/shader_material.hpp
using UniformValue = std::variant<int, float, Color, Matrix3, Matrix4, Vector2, Vector3, Vector4>;

class GLUniform {
public:
    GLUniform(const std::string& name, GLint location, GLint size, GLenum type);

    auto SetValueIfNeeded(const UniformValue& v) -> void;

    auto UpdateUniformIfNeeded() -> void;

    const auto& Value() const { return value_; }

private:
    std::string name_ {};
    UniformValue value_ {};
    GLint location_ {0};
    GLint size_ {0};
    GLenum type_ {0};

    bool needs_update_ {true};

    template <typename... T>
    auto SetValue(const UniformValue& v) -> bool {
        return ((SetValueHelper<T>(v)) || ...);
    }

    template <typename T>
    auto SetValueHelper(const UniformValue& v) -> bool {
        if (const auto* f = std::get_if<T>(&v)) {
            value_ = *f;
            return true;
        }
        return false;
    }

    auto GLenumToString(GLenum type) const -> const char*;
};

}