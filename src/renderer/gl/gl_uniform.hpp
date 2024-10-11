// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/color.hpp"
#include "engine/math/matrix4.hpp"
#include "engine/math/vector4.hpp"

#include "core/logger.hpp"

#include <variant>

#include <glad/glad.h>

namespace engine {

using GLUniformValue = std::variant<float, Color, Matrix4, Vector4>;

class GLUniform {
public:
    GLUniformValue value {};
    GLint location {0};
    GLint size {0};
    GLenum type {0};
    bool needs_update {false};

    auto Set(std::string_view name, const GLUniformValue& v) {
        if (SetValueByType(name, v)) {
            needs_update = true;
        } else {
            Logger::Log(
                LogLevel::Error,
                "Failed to set uniform '{}' with unsupported type: {}",
                name, GLenumToString(type)
            );
        }
    }

    auto UpdateUniformIfNeeded() {
        if (!needs_update) return;

        switch (type) {
            case GL_FLOAT:
                glUniform1f(location, *reinterpret_cast<const GLfloat*>(&value));
            break;
            case GL_FLOAT_VEC4:
                glUniform4fv(location, 1, reinterpret_cast<const GLfloat*>(&value));
            break;
            case GL_FLOAT_MAT4:
                glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&value));
            break;
        }

        needs_update = false;
    }

private:
    auto SetValueByType(std::string_view name, const GLUniformValue& v) -> bool {
        switch (type) {
            case GL_FLOAT:
                return SetValue<float>(name, v);
            case GL_FLOAT_VEC4:
                return SetValue<Color, Vector4>(name, v);
            case GL_FLOAT_MAT4:
                return SetValue<Matrix4>(name, v);
            default:
                return false;
        }
    }

    template <typename... T>
    auto SetValue(std::string_view name, const GLUniformValue& v) -> bool {
        return ((SetValueHelper<T>(v)) || ...);
    }

    template <typename T>
    auto SetValueHelper(const GLUniformValue& v) -> bool {
        if (const auto* f = std::get_if<T>(&v)) {
            value = *f;
            return true;
        }
        return false;
    }

    auto GLenumToString(GLenum type) const -> const char* {
        switch (type) {
            case GL_FLOAT: return "GL_FLOAT";
            case GL_FLOAT_VEC4: return "GL_FLOAT_VEC4";
            case GL_FLOAT_MAT4: return "GL_FLOAT_MAT4";
            default: return "Unknown";
        }
    }
};

}