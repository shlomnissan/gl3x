// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/scene/mesh.hpp"

#include "renderer/gl/gl_program.hpp"

#include <memory>
#include <string>
#include <unordered_map>

namespace engine {

class GLPrograms {
public:
    auto GetProgram(Mesh* mesh) -> GLProgram*;

private:
    std::unordered_map<std::string, std::unique_ptr<GLProgram>> programs_ {};
};

}