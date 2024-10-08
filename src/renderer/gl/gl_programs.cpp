// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_programs.hpp"

#include "core/logger.hpp"

#include <vector>

namespace engine {

auto GLPrograms::GetProgram(Mesh* mesh) -> GLProgram* {
    auto material = mesh->GetMaterial();

    if (!programs_.contains(material->Type())) {
        Logger::Log(LogLevel::Info, "Creating a new shader program {}", *material);

        programs_[material->Type()] = std::make_unique<GLProgram>(
            shader_lib_.GetShaderSource(material)
        );
    }
    return programs_[material->Type()].get();
}

}