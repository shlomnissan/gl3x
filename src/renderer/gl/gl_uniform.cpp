// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_uniform.hpp"

namespace engine {

GLUniform::GLUniform(const std::string& name, GLint location, GLint size, GLenum type)
  : name_(name),
    location_(location),
    size_(size),
    type_(type) {}

auto GLUniform::SetValueIfNeeded(const GLUniformValue& v) -> void {
    if (value_ == v && !needs_update_) return;

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
            return;
            break;
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

    // - This list is incomplete. Add new types as needed.
    // - We use reinterpret_cast because multiple values can map onto the same GL type.
    //   For instance, both Vector4 and Color map to GL_FLOAT_VEC4.
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
        case GL_FLOAT_VEC2: return "GL_FLOAT_VEC2";
        case GL_FLOAT_VEC3: return "GL_FLOAT_VEC3";
        case GL_FLOAT_VEC4: return "GL_FLOAT_VEC4";
        case GL_INT: return "GL_INT";
        case GL_INT_VEC2: return "GL_INT_VEC2";
        case GL_INT_VEC3: return "GL_INT_VEC3";
        case GL_INT_VEC4: return "GL_INT_VEC4";
        case GL_UNSIGNED_INT: return "GL_UNSIGNED_INT";
        case GL_UNSIGNED_INT_VEC2: return "GL_UNSIGNED_INT_VEC2";
        case GL_UNSIGNED_INT_VEC3: return "GL_UNSIGNED_INT_VEC3";
        case GL_UNSIGNED_INT_VEC4: return "GL_UNSIGNED_INT_VEC4";
        case GL_BOOL: return "GL_BOOL";
        case GL_BOOL_VEC2: return "GL_BOOL_VEC2";
        case GL_BOOL_VEC3: return "GL_BOOL_VEC3";
        case GL_BOOL_VEC4: return "GL_BOOL_VEC4";
        case GL_FLOAT_MAT2: return "GL_FLOAT_MAT2";
        case GL_FLOAT_MAT3: return "GL_FLOAT_MAT3";
        case GL_FLOAT_MAT4: return "GL_FLOAT_MAT4";
        case GL_FLOAT_MAT2x3: return "GL_FLOAT_MAT2x3";
        case GL_FLOAT_MAT2x4: return "GL_FLOAT_MAT2x4";
        case GL_FLOAT_MAT3x2: return "GL_FLOAT_MAT3x2";
        case GL_FLOAT_MAT3x4: return "GL_FLOAT_MAT3x4";
        case GL_FLOAT_MAT4x2: return "GL_FLOAT_MAT4x2";
        case GL_FLOAT_MAT4x3: return "GL_FLOAT_MAT4x3";
        case GL_SAMPLER_2D: return "GL_SAMPLER_2D";
        case GL_SAMPLER_3D: return "GL_SAMPLER_3D";
        case GL_SAMPLER_CUBE: return "GL_SAMPLER_CUBE";
        case GL_SAMPLER_2D_SHADOW: return "GL_SAMPLER_2D_SHADOW";
        case GL_SAMPLER_2D_ARRAY: return "GL_SAMPLER_2D_ARRAY";
        case GL_SAMPLER_2D_ARRAY_SHADOW: return "GL_SAMPLER_2D_ARRAY_SHADOW";
        case GL_SAMPLER_CUBE_SHADOW: return "GL_SAMPLER_CUBE_SHADOW";
        case GL_SAMPLER_BUFFER: return "GL_SAMPLER_BUFFER";
        case GL_SAMPLER_2D_MULTISAMPLE: return "GL_SAMPLER_2D_MULTISAMPLE";
        case GL_SAMPLER_2D_MULTISAMPLE_ARRAY: return "GL_SAMPLER_2D_MULTISAMPLE_ARRAY";
        case GL_SAMPLER_CUBE_MAP_ARRAY: return "GL_SAMPLER_CUBE_MAP_ARRAY";
        case GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW: return "GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW";
        case GL_INT_SAMPLER_2D: return "GL_INT_SAMPLER_2D";
        case GL_INT_SAMPLER_3D: return "GL_INT_SAMPLER_3D";
        case GL_INT_SAMPLER_CUBE: return "GL_INT_SAMPLER_CUBE";
        case GL_INT_SAMPLER_2D_ARRAY: return "GL_INT_SAMPLER_2D_ARRAY";
        case GL_UNSIGNED_INT_SAMPLER_2D: return "GL_UNSIGNED_INT_SAMPLER_2D";
        case GL_UNSIGNED_INT_SAMPLER_3D: return "GL_UNSIGNED_INT_SAMPLER_3D";
        case GL_UNSIGNED_INT_SAMPLER_CUBE: return "GL_UNSIGNED_INT_SAMPLER_CUBE";
        case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY: return "GL_UNSIGNED_INT_SAMPLER_2D_ARRAY";
        default: return "Unknown";
    }
}

}