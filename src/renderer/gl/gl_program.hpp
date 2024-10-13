// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "renderer/gl/gl_uniform.hpp"

#include <string>
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

    auto UpdateUniformsIfNeeded() -> void;

    auto Use() const -> void;

    auto SetUniform(const std::string& name, const GLUniformValue& v) -> void;

    ~GLProgram();

private:
    GLuint program_ {0};

    std::unordered_map<std::string, GLUniform> uniforms_ {};

    auto BindVertexAttributes() const -> void;

    auto GetUniformLoc(const std::string& name) const -> int;

    auto ProcessUniforms() -> void;

    auto CheckProgramLinkStatus() const -> bool;

    auto CheckShaderCompileStatus(GLuint shader_id) const -> bool;

    auto GetShaderType(ShaderType type) const -> GLuint;
};

}