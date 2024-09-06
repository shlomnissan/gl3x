// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/temp/shader_temp.hpp>

#include <iostream>
#include <string>

#include <fmt/format.h>

namespace engine {

ShaderTemp::ShaderTemp(const std::vector<ShaderInfo>& shaders) {
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

auto ShaderTemp::Use() const -> void {
    glUseProgram(program_);
}

auto ShaderTemp::GetShaderType(ShaderType type) const -> unsigned int {
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

auto ShaderTemp::GetShaderTypeString(ShaderType type) const -> const char* {
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

auto ShaderTemp::CheckShaderCompileStatus(GLuint shader_id, ShaderType type) const -> void {
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

auto ShaderTemp::CheckProgramLinkStatus() const -> void {
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

auto ShaderTemp::GetUniform(std::string_view name) const -> GLint {
    Use();
    auto loc = glGetUniformLocation(program_, name.data());
    if (loc < 0) {
        throw ShaderError {
            fmt::format("Uniform '{}' not found", name)
        };
    }
    return loc;
}

auto ShaderTemp::SetUniform(std::string_view u, const engine::Matrix4& m) const -> void {
    glUniformMatrix4fv(GetUniform(u), 1, GL_FALSE, &m(0, 0));
}

ShaderTemp::~ShaderTemp() {
    if (program_) {
        glDeleteProgram(program_);
    }
}

}