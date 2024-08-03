// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "shader.h"

#include <iostream>
#include <string>

#include <fmt/format.h>

Shader::Shader(const std::vector<ShaderInfo>& shaders) {
    program_ = glCreateProgram();

    for (const auto& shader_info : shaders) {
        auto shader_id = glCreateShader(GetShaderType(shader_info.type));
        auto data = shader_info.source.data();

        glShaderSource(shader_id, 1, &data, nullptr);
        glCompileShader(shader_id);

        CheckShaderCompileStatus(shader_id, shader_info.type);

        glAttachShader(program_, shader_id);
        glDeleteShader(shader_id);
    }

    glLinkProgram(program_);
    CheckProgramLinkStatus();
}

auto Shader::Use() const -> void {
    glUseProgram(program_);
}

auto Shader::GetShaderType(ShaderType type) const -> unsigned int {
    switch(type) {
        case ShaderType::kVertexShader:
            return GL_VERTEX_SHADER;
            break;
        case ShaderType::kFragmentShader:
            return GL_FRAGMENT_SHADER;
            break;
        default:
            throw ShaderError {"Unsupported Shader Type"};
    }
}

auto Shader::GetShaderTypeString(ShaderType type) const -> const char* {
    switch (type) {
        case ShaderType::kVertexShader:
            return "Vertex";
            break;
        case ShaderType::kFragmentShader:
            return "Fragment";
            break;
        default:
            throw ShaderError {"Unsupported shader type"};
    }
}

auto Shader::CheckShaderCompileStatus(GLuint shader_id, ShaderType type) const -> void {
    auto success = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        auto buffer = std::string{"", 512};
        glGetShaderInfoLog(shader_id, static_cast<int>(buffer.size()), nullptr, buffer.data());

        auto message = fmt::format(
            "{} shader compilation error\n{}", GetShaderTypeString(type), buffer
        );
        std::cerr << message << '\n';

        throw ShaderError {message};
    }
}

auto Shader::CheckProgramLinkStatus() const -> void {
    auto success = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (!success) {
        auto buffer = std::string{"", 512};
        glGetProgramInfoLog(program_, static_cast<int>(buffer.size()), nullptr, buffer.data());

        auto message = fmt::format("Shader program link error:\n{}", buffer);
        std::cerr << message << '\n';

        throw ShaderError {message};
    }
}

auto Shader::GetUniform(std::string_view name) const -> GLint {
    Use();
    auto loc = glGetUniformLocation(program_, name.data());
    if (loc < 0) {
        throw ShaderError {
            fmt::format("Uniform '{}' not found", name)
        };
    }
    return loc;
}

auto Shader::SetUniform(std::string_view uniform, int i) const -> void {
    glUniform1i(GetUniform(uniform), i);
}

auto Shader::SetUniform(std::string_view uniform, const float f) const -> void {
    glUniform1f(GetUniform(uniform), f);
}

auto Shader::SetUniform(std::string_view uniform, const glm::vec3& vec) const -> void {
    glUniform3fv(GetUniform(uniform), 1, &vec[0]);
}

auto Shader::SetUniform(std::string_view uniform, const glm::mat3& matrix) const -> void {
    glUniformMatrix3fv(GetUniform(uniform), 1, GL_FALSE, &matrix[0][0]);
}

auto Shader::SetUniform(std::string_view uniform, const glm::mat4& matrix) const -> void {
    glUniformMatrix4fv(GetUniform(uniform), 1, GL_FALSE, &matrix[0][0]);
}

Shader::~Shader() {
    if (program_) {
        glDeleteProgram(program_);
    }
}