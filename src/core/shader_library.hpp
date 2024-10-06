// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "materials/material.hpp"

#include <string_view>
#include <vector>

namespace engine {

enum class ShaderType {
    kVertexShader,
    kFragmentShader
};

struct ShaderInfo {
    ShaderType type;
    std::string_view source;
};

class ShaderLibrary {
public:
    auto GetShaderSource(Material* material) -> std::vector<ShaderInfo>;
};

}