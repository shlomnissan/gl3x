// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "core/program_attributes.hpp"

#include <string_view>
#include <vector>

namespace engine {

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
    auto InjectAttributes(const ProgramAttributes& attrs, std::string_view source) const -> std::string;
};

}