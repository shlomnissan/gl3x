/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "core/program_attributes.hpp"

#include <string_view>
#include <vector>

namespace gl3x {

enum class ShaderType {
    kVertexShader,
    kFragmentShader
};

struct ShaderInfo {
    ShaderType type;
    std::string source;
};

class ShaderLibrary {
public:
    auto GetShaderSource(const ProgramAttributes& attrs) const -> std::vector<ShaderInfo>;

private:
    auto ProcessShader(const ProgramAttributes& attrs, std::string_view source) const -> std::string;

    auto InjectAttributes(const ProgramAttributes& attrs, std::string& source) const -> void;

    auto ResolveIncludes(std::string& source) const -> void;
};

}