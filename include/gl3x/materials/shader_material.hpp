/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/materials/material.hpp"

#include "gl3x/math/color.hpp"
#include "gl3x/math/matrix3.hpp"
#include "gl3x/math/matrix4.hpp"
#include "gl3x/math/vector2.hpp"
#include "gl3x/math/vector3.hpp"
#include "gl3x/math/vector4.hpp"

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>

namespace gl3x {

/**
 * @brief Variant type for shader material uniform values.
 *
 * @ingroup MaterialsGroup
 */
using UniformValue = std::variant<int, float, Color, Matrix3, Matrix4, Vector2, Vector3, Vector4>;

/**
 * @brief Represents a material rendered with custom shaders.
 *
 * This material allows rendering with user-defined GLSL shaders.
 * It is suitable for advanced effects, custom lighting, and any scenario
 * requiring programmable control over the rendering pipeline.
 *
 * @code
 * auto material = gl3x::ShaderMaterial::Create({
 *   vertex_shader_str,
 *   fragment_shader_str,
 *   {
 *     // custom uniforms
 *     {"u_Time", 0.0f},
 *     {"u_Resolution", Vector2::Zero }
 *   }
 * });
 *
 * auto mesh = gl3x::Mesh::Create(geometry, material);
 * scene->Add(mesh);
 * @endcode
 *
 * @ingroup MaterialsGroup
 */
class GL3X_EXPORT ShaderMaterial : public Material {
public:
    friend class ProgramAttributes;

    /// @brief Stores values for custom uniforms used by the shader.
    std::unordered_map<std::string, UniformValue> uniforms;

    /**
     * @brief Constructs a ShaderMaterial object.
     *
     * @param vertex_shader Vertex shader GLSL source-code.
     * @param fragment_shader Fragment shader GLSL source-code.
     * @param uniforms Custom uniforms used by the shader.
     */
    ShaderMaterial(
        std::string_view vertex_shader,
        std::string_view fragment_shader,
        const std::unordered_map<std::string, UniformValue>& uniforms
    ) : vertex_shader_(vertex_shader),
        fragment_shader_(fragment_shader),
        uniforms(uniforms) {}

    /**
     * @brief Creates a shared pointer to a ShaderMaterial object.
     *
     * @param vertex_shader Vertex shader GLSL source-code.
     * @param fragment_shader Fragment shader GLSL source-code.
     * @param uniforms Custom uniforms used by the shader.
     * @return std::shared_ptr<ShaderMaterial>
     */
    [[nodiscard]] static auto Create(
        std::string_view vertex_shader,
        std::string_view fragment_shader,
        const std::unordered_map<std::string, UniformValue>& uniforms
    ) {
        return std::make_shared<ShaderMaterial>(vertex_shader, fragment_shader, uniforms);
    }

    /**
     * @brief Returns material type.
     *
     * @return MaterialType::ShaderMaterial
     */
    auto GetType() const -> MaterialType override {
        return MaterialType::ShaderMaterial;
    }

private:
    /// @brief Vertex shader GLSL source-code.
    std::string vertex_shader_;

    /// @brief Fragment shader GLSL source-code.
    std::string fragment_shader_;
};

}