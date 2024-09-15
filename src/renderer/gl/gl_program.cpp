// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_program.hpp"

#include <iostream>

#include <fmt/format.h>

namespace engine {

GLProgram::GLProgram(const std::vector<GLShaderInfo>& shaders) {
    program_ = glCreateProgram();

    for (const auto& shader_info : shaders) {
        auto shader_id = glCreateShader(GetShaderType(shader_info.type));
        auto data = shader_info.source.data();

        glShaderSource(shader_id, 1, &data, nullptr);
        glCompileShader(shader_id);

        if (!CheckShaderCompileStatus(shader_id)) {
            break;
        }

        glAttachShader(program_, shader_id);
        glDeleteShader(shader_id);
    }

    glLinkProgram(program_);
    CheckProgramLinkStatus();
}

auto GLProgram::Use() const -> void {
    glUseProgram(program_);
}

auto GLProgram::GetUniformLoc(std::string_view name) const -> int {
    return glGetUniformLocation(program_, name.data());
}

auto GLProgram::SetUniform(std::string_view name, const engine::Matrix4& m) const -> void {
    glUniformMatrix4fv(GetUniformLoc(name), 1, GL_FALSE, &m(0, 0));
}

auto GLProgram::CheckShaderCompileStatus(GLuint shader_id) const -> bool {
    auto success = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        auto buffer = std::string{"", 512};
        glGetShaderInfoLog(shader_id, static_cast<int>(buffer.size()), nullptr, buffer.data());
        auto message = fmt::format("Shader compilation error\n{}", buffer);
        std::cerr << message << '\n';
    }
    return success;
}

auto GLProgram::CheckProgramLinkStatus() const -> bool {
    auto success = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (!success) {
        auto buffer = std::string{"", 512};
        glGetProgramInfoLog(program_, static_cast<int>(buffer.size()), nullptr, buffer.data());
        auto message = fmt::format("Shader program link error:\n{}", buffer);
        std::cerr << message << '\n';
    }
    return success;
}

auto GLProgram::GetShaderType(GLShaderType type) const -> GLuint {
    switch(type) {
        case GLShaderType::kVertexShader:
            return GL_VERTEX_SHADER;
        case GLShaderType::kFragmentShader:
            return GL_FRAGMENT_SHADER;
        default:
            return -1;
    }
}

}