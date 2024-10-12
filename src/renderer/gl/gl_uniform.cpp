// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_uniform.hpp"

namespace engine {

GLUniform::GLUniform(const std::string& name, GLint location, GLint size, GLenum type)
  : name_(name),
    location_(location),
    size_(size),
    type_(type) {}

auto GLUniform::Set(const GLUniformValue& v) -> void {
    auto is_set = false;

    switch (type_) {
        case GL_INT:
        case GL_SAMPLER_2D:
            is_set = SetValue<GLint>(v);
            break;
        case GL_FLOAT:
            is_set = SetValue<GLfloat>(v);
            break;
        case GL_FLOAT_VEC4:
            is_set = SetValue<Color, Vector4>(v);
            break;
        case GL_FLOAT_MAT4:
            is_set = SetValue<Matrix4>(v);
            break;
        default:
            Logger::Log(
                LogLevel::Error,
                "Failed to set uniform '{}' with unsupported type {}",
                name_, GLenumToString(type_)
            );
    }

    if (is_set) {
        needs_update_ = true;
    } else {
        Logger::Log(
            LogLevel::Error,
            "Failed to set uniform '{}'. The underlying data type is unsupported",
            name_, GLenumToString(type_)
        );
    }
}

auto GLUniform::UpdateUniformIfNeeded() -> void {
    if (!needs_update_) return;

    switch (type_) {
        case GL_INT:
        case GL_SAMPLER_2D:
            glUniform1i(location_, *reinterpret_cast<const GLint*>(&value_));
        break;
        case GL_FLOAT:
            glUniform1f(location_, *reinterpret_cast<const GLfloat*>(&value_));
        break;
        case GL_FLOAT_VEC4:
            glUniform4fv(location_, 1, reinterpret_cast<const GLfloat*>(&value_));
        break;
        case GL_FLOAT_MAT4:
            glUniformMatrix4fv(location_, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&value_));
        break;
    }

    needs_update_ = false;
}

auto GLUniform::GLenumToString(GLenum type) const -> const char* {
    switch (type) {
        case GL_FLOAT: return "GL_FLOAT";
        case GL_FLOAT_VEC4: return "GL_FLOAT_VEC4";
        case GL_FLOAT_MAT4: return "GL_FLOAT_MAT4";
        case GL_SAMPLER_2D: return "GL_SAMPLER_2D";
        default: return "Unknown";
    }
}

}