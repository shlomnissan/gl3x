// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <stdexcept>
#include <string_view>
#include <vector>

#include <glad/glad.h>

#include <engine/math.hpp>

namespace engine {

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

    auto SetUniform(std::string_view u, const engine::Matrix4& m) const -> void;

    ~Shader();

private:
    GLuint program_;

    auto CheckProgramLinkStatus() const -> void;
    auto CheckShaderCompileStatus(GLuint shader_id, ShaderType type) const -> void;

    auto GetShaderType(ShaderType type) const -> GLuint;
    auto GetShaderTypeString(ShaderType type) const -> const char*;
};

struct ShaderError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

}
