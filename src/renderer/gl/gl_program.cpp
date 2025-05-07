// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "renderer/gl/gl_program.hpp"

#include "engine/core/geometry.hpp"

#include "core/shader_library.hpp"
#include "utilities/logger.hpp"

#include <utility>

namespace engine {

static const auto VertexAttributesMap = std::unordered_map<std::string, GeometryAttributeType> {
    {"a_Position", GeometryAttributeType::Position},
    {"a_Normal", GeometryAttributeType::Normal},
    {"a_TexCoord", GeometryAttributeType::UV}
};

GLProgram::GLProgram(const std::vector<ShaderInfo>& shaders) {
    program_ = glCreateProgram();

    auto compilation_error = false;
    for (const auto& shader_info : shaders) {
        auto shader_id = glCreateShader(GetShaderType(shader_info.type));
        auto data = shader_info.source.data();

        glShaderSource(shader_id, 1, &data, nullptr);
        glCompileShader(shader_id);

        if (!CheckShaderCompileStatus(shader_id)) {
            compilation_error = true;
            break;
        }

        glAttachShader(program_, shader_id);
        glDeleteShader(shader_id);
    }

    if (compilation_error) {
        has_errors_ = true;
        return;
    }

    BindVertexAttributeLocations();

    glLinkProgram(program_);
    if (!CheckProgramLinkStatus()) {
        has_errors_ = true;
        return;
    }

    ProcessUniforms();
}

auto GLProgram::UpdateUniforms() -> void {
    for (auto& [_, uniform] : uniforms_) {
        uniform.UpdateUniformIfNeeded();
    }
}

auto GLProgram::Use() const -> void {
    glUseProgram(program_);
}

auto GLProgram::SetUniformIfExists(const std::string& name, const UniformValue& v) -> void {
    if (uniforms_.contains(name)) {
        SetUniform(name, v);
    }
}

auto GLProgram::SetUniform(const std::string& name, const UniformValue& v) -> void {
    if (!uniforms_.contains(name)) {
        Logger::Log(LogLevel::Error, "Uniform {} is not found", name);
        return;
    }
    uniforms_.at(name).SetValueIfNeeded(v);
}

auto GLProgram::BindVertexAttributeLocations() const -> void {
    for (auto& [attr_name, attr_type] : VertexAttributesMap) {
        glBindAttribLocation(
            program_,
            std::to_underlying(attr_type),
            attr_name.data()
        );
    }
}

auto GLProgram::GetUniformLoc(std::string_view name) const -> int {
    return glGetUniformLocation(program_, name.data());
}

auto GLProgram::ProcessUniforms() -> void {
    auto n_active_uniforms = GLint {0};
    glGetProgramiv(program_, GL_ACTIVE_UNIFORMS, &n_active_uniforms);

    auto max_name_length = GLsizei {0};
    glGetProgramiv(program_, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_length);

    auto buffer = std::string {"", static_cast<size_t>(max_name_length)};
    auto length = GLsizei {};
    auto size = GLint {};
    auto type = GLenum {};

    for (auto i = 0; i < n_active_uniforms; ++i) {
        glGetActiveUniform(
            program_, i,
            max_name_length,
            &length,
            &size,
            &type,
            buffer.data()
        );

        auto name = std::string(buffer.data(), length);
        uniforms_.try_emplace(name, name, GetUniformLoc(name), size, type);
    }
}

auto GLProgram::CheckShaderCompileStatus(GLuint shader_id) const -> bool {
    auto success = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        auto length = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        auto buffer = std::string {"", static_cast<size_t>(length)};
        glGetShaderInfoLog(shader_id, length, nullptr, buffer.data());
        Logger::Log(LogLevel::Error, "Shader compilation error {}", buffer);
    }
    return success;
}

auto GLProgram::CheckProgramLinkStatus() const -> bool {
    auto success = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        auto length = 0;
        glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &length);
        auto buffer = std::string {"", static_cast<size_t>(length)};
        glGetProgramInfoLog(program_, length, nullptr, buffer.data());
        Logger::Log(LogLevel::Error, "Shader program link error {}", buffer);
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