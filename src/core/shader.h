// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <stdexcept>
#include <string_view>
#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>

enum class ShaderType {
    kVertexShader,
    kFragmentShader
};

struct ShaderInfo {
    ShaderType type;
    std::string_view source;
};

class Shader {
public:
    explicit Shader(const std::vector<ShaderInfo>& shaders);

    auto Use() const -> void;

    auto GetUniform(std::string_view name) const -> GLint;
    auto SetInt(std::string_view uniform, int i) const -> void;
    auto SetFloat(std::string_view uniform, const float f) const -> void;
    auto SetVec3(std::string_view uniform, const glm::vec3& vec) const -> void;
    auto SetMat4(std::string_view uniform, const glm::mat4& matrix) const -> void;

    ~Shader();

private:
    GLuint program_;

    auto GetShaderType(ShaderType type) const -> GLuint;
    auto GetShaderTypeString(ShaderType type) const -> const char*;
    auto CheckShaderCompileStatus(GLuint shader_id, ShaderType type) const -> void;
    auto CheckProgramLinkStatus() const -> void;
};

struct ShaderError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};