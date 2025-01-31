// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/materials/material.hpp"

#include "engine/math/color.hpp"
#include "engine/math/matrix3.hpp"
#include "engine/math/matrix4.hpp"
#include "engine/math/vector2.hpp"
#include "engine/math/vector3.hpp"
#include "engine/math/vector4.hpp"

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>

namespace engine {

// UniformValue is also defined in include/renderer/gl/gl_uniform.hpp
using UniformValue = std::variant<int, float, Color, Matrix3, Matrix4, Vector2, Vector3, Vector4>;
using Uniforms = std::unordered_map<std::string, UniformValue>;

/**
 * @brief A material rendered with custom shaders.
 */
class ENGINE_EXPORT ShaderMaterial : public Material {
public:
    friend class ProgramAttributes;

    /// @brief The uniform values for the shader.
    std::unordered_map<std::string, UniformValue> uniforms;

    /**
     * @brief Construct a new Shader Material object.
     *
     * @param vertex_shader The vertex shader source code.
     * @param fragment_shader The fragment shader source code.
     * @param uniforms The uniform values for the shader.
     */
    ShaderMaterial(
        std::string_view vertex_shader,
        std::string_view fragment_shader,
        const Uniforms& uniforms
    ) :
        vertex_shader_(vertex_shader),
        fragment_shader_(fragment_shader),
        uniforms(uniforms) {}

    /**
     * @brief Retrieves the type of the material.
     *
     * @return The type of the material as `MaterialType::ShaderMaterial`.
     */
    auto Type() const -> MaterialType override {
        return MaterialType::ShaderMaterial;
    }

    /**
     * @brief Creates a new instance of ShaderMaterial.
     *
     * @param vertex_shader The vertex shader source code.
     * @param fragment_shader The fragment shader source code.
     * @param uniforms The uniform values for the shader.
     * @return A `std::shared_ptr` to a new instance of ShaderMaterial.
     */
    [[nodiscard]] static auto Create(
        std::string_view vertex_shader,
        std::string_view fragment_shader,
        const Uniforms& uniforms
    ) {
        return std::make_shared<ShaderMaterial>(vertex_shader, fragment_shader, uniforms);
    }

private:
    /// @brief The vertex shader source code.
    std::string vertex_shader_;

    /// @brief The fragment shader source code.
    std::string fragment_shader_;
};

}