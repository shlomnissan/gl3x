// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_program.hpp"

#include "core/shader_library.hpp"
#include "core/logger.hpp"

namespace engine {

GLProgram::GLProgram(const std::vector<ShaderInfo>& shaders) {
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

auto GLProgram::SetUniform(std::string_view name, const engine::Color& c) const -> void {
    glUniform4fv(GetUniformLoc(name), 1, &c[0]);
}

auto GLProgram::CheckShaderCompileStatus(GLuint shader_id) const -> bool {
    auto success = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        auto buffer = std::string {"", 512};
        glGetShaderInfoLog(shader_id, static_cast<int>(buffer.size()), nullptr, buffer.data());
        Logger::Log(LogLevel::Error, "Shader compilation error", buffer);
    }
    return success;
}

auto GLProgram::CheckProgramLinkStatus() const -> bool {
    auto success = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (!success) {
        auto buffer = std::string {"", 512};
        glGetProgramInfoLog(program_, static_cast<int>(buffer.size()), nullptr, buffer.data());
        Logger::Log(LogLevel::Error, "Shader program link error", buffer);
    }
    return success;
}

auto GLProgram::GetShaderType(ShaderType type) const -> GLuint {
    switch(type) {
        case ShaderType::kVertexShader:
            return GL_VERTEX_SHADER;
        case ShaderType::kFragmentShader:
            return GL_FRAGMENT_SHADER;
        default:
            return -1;
    }
}

GLProgram::~GLProgram() {
    if (program_ > 0) glDeleteProgram(program_);
}

}