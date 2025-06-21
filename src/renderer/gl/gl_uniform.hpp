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
    Color,
    FogColor,
    FogDensity,
    FogFar,
    FogNear,
    FogType,
    MaterialDiffuseColor,
    MaterialShininess,
    MaterialSpecularColor,
    Model,
    Opacity,
    Resolution,
    TextureMap,
    TextureTransform,
    KnownUniformsLength
};

constexpr auto get_uniform_loc(std::string_view str) {
    using enum Uniform;
    if (str == "u_Color") return static_cast<int>(Color);
    if (str == "u_Fog.Color") return static_cast<int>(FogColor);
    if (str == "u_Fog.Density") return static_cast<int>(FogDensity);
    if (str == "u_Fog.Far") return static_cast<int>(FogFar);
    if (str == "u_Fog.Near") return static_cast<int>(FogNear);
    if (str == "u_Fog.Type") return static_cast<int>(FogType);
    if (str == "u_Material.DiffuseColor") return static_cast<int>(MaterialDiffuseColor);
    if (str == "u_Material.Shininess") return static_cast<int>(MaterialShininess);
    if (str == "u_Material.SpecularColor") return static_cast<int>(MaterialSpecularColor);
    if (str == "u_Model") return static_cast<int>(Model);
    if (str == "u_Opacity") return static_cast<int>(Opacity);
    if (str == "u_Resolution") return static_cast<int>(Resolution);
    if (str == "u_TextureMap") return static_cast<int>(TextureMap);
    if (str == "u_TextureTransform") return static_cast<int>(TextureTransform);
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