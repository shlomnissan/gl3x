// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/color.hpp"
#include "engine/math/matrix4.hpp"

#include "core/shader_library.hpp"

#include <string_view>
#include <vector>

#include <glad/glad.h>

namespace engine {

class GLProgram {
public:
    explicit GLProgram(const std::vector<ShaderInfo>& shaders);

    GLProgram(const GLProgram&) = delete;
    GLProgram(GLProgram&&) = delete;
    GLProgram& operator=(const GLProgram&) = delete;
    GLProgram& operator=(GLProgram&&) = delete;

    auto Use() const -> void;

    auto GetUniformLoc(std::string_view name) const -> int;

    auto SetUniform(std::string_view name, const engine::Matrix4& m) const -> void;

    auto SetUniform(std::string_view name, const engine::Color& c) const -> void;

    ~GLProgram();

private:
    GLuint program_;

    auto CheckProgramLinkStatus() const -> bool;

    auto CheckShaderCompileStatus(GLuint shader_id) const -> bool;

    auto GetShaderType(ShaderType type) const -> GLuint;
};

}