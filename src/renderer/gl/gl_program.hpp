// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <string_view>
#include <vector>

#include <glad/glad.h>

#include "engine/math/matrix4.hpp"

namespace engine {

enum class GLShaderType {
    kVertexShader,
    kFragmentShader
};

struct GLShaderInfo {
    GLShaderType type;
    std::string_view source;
};

class GLProgram {
public:
    explicit GLProgram(const std::vector<GLShaderInfo>& shaders);

    GLProgram(const GLProgram&) = delete;
    GLProgram(GLProgram&&) = delete;
    GLProgram& operator=(const GLProgram&) = delete;
    GLProgram& operator=(GLProgram&&) = delete;

    auto Use() const -> void;

    auto GetUniformLoc(std::string_view name) const -> int;

    auto SetUniform(std::string_view name, const engine::Matrix4& m) const -> void;

private:
    GLuint program_;

    auto CheckProgramLinkStatus() const -> bool;

    auto CheckShaderCompileStatus(GLuint shader_id, GLShaderType type) const -> bool;

    auto GetShaderType(GLShaderType type) const -> GLuint;
};

}