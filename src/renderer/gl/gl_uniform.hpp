/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/math/color.hpp"
#include "gleam/math/matrix3.hpp"
#include "gleam/math/matrix4.hpp"
#include "gleam/math/vector2.hpp"
#include "gleam/math/vector3.hpp"
#include "gleam/math/vector4.hpp"

#include <string>

#include <glad/glad.h>

namespace gleam {

enum class UniformType {
    Float,
    Int,
    Matrix3,
    Matrix4,
    Vector2,
    Vector3,
    Vector4,
    Unsupported
};

enum class Uniform {
    Color = 0,
    Model,
    Opacity,
    Projection,
    Resolution,
    TextureMap,
    TextureTransform,
    View,
    KnownUniformsLength
};

constexpr std::pair<std::string_view, Uniform> known_uniform_map[] = {
    {"u_Color", Uniform::Color},
    {"u_Model", Uniform::Model},
    {"u_Opacity", Uniform::Opacity},
    {"u_Projection", Uniform::Projection},
    {"u_Resolution", Uniform::Resolution},
    {"u_TextureMap", Uniform::TextureMap},
    {"u_TextureTransform", Uniform::TextureTransform},
    {"u_View", Uniform::View},
};

constexpr auto uniform_index(std::string_view str) {
    using enum Uniform;
    if (str == "u_Color") return static_cast<int>(Color);
    if (str == "u_Model") return static_cast<int>(Model);
    if (str == "u_Opacity") return static_cast<int>(Opacity);
    if (str == "u_Projection") return static_cast<int>(Projection);
    if (str == "u_Resolution") return static_cast<int>(Resolution);
    if (str == "u_TextureMap") return static_cast<int>(TextureMap);
    if (str == "u_TextureTransform") return static_cast<int>(TextureTransform);
    if (str == "u_View") return static_cast<int>(View);
    return -1;
}

class GLUniform {
public:
    GLUniform(std::string_view name, GLint location, GLenum type);

    auto SetValue(const void* value) -> void;

    auto UploadIfNeeded() -> void;

private:
    std::string name_;

    GLint location_ {-1};

    UniformType type_;

    bool needs_upload_ {false};

    union {
        GLfloat f;
        GLint   i;
        Matrix3 m3;
        Matrix4 m4;
        Vector2 v2;
        Vector3 v3;
        Vector4 v4;
    } data_;
};

}