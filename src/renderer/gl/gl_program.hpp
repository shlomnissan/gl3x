// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "renderer/gl/gl_uniform.hpp"

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <glad/glad.h>

namespace engine {

#pragma region Forward Declarations

enum class ShaderType;

struct ShaderInfo;

#pragma endregion

class GLProgram {
public:
    explicit GLProgram(const std::vector<ShaderInfo>& shaders);

    GLProgram(const GLProgram&) = delete;
    GLProgram(GLProgram&&) = delete;
    GLProgram& operator=(const GLProgram&) = delete;
    GLProgram& operator=(GLProgram&&) = delete;

    auto UpdateUniforms() -> void;

    auto Use() const -> void;

    auto IsValid() const { return !has_errors_ && program_ > 0; }

    auto SetUniformIfExists(const std::string& name, const UniformValue& v) -> void;

    auto SetUniform(const std::string& name, const UniformValue& v) -> void;

    ~GLProgram();

private:
    std::unordered_map<std::string, GLUniform> uniforms_ {};

    GLuint program_ {0};

    bool has_errors_ {false};

    auto BindVertexAttributeLocations() const -> void;

    auto GetUniformLoc(std::string_view name) const -> int;

    auto ProcessUniforms() -> void;

    auto CheckProgramLinkStatus() const -> bool;

    auto CheckShaderCompileStatus(GLuint shader_id) const -> bool;

    auto GetShaderType(ShaderType type) const -> GLuint;
};

}