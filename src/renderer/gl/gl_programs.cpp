// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_programs.hpp"

#include "engine/core/logger.hpp"

#include <vector>

namespace engine {

auto GLPrograms::GetProgram(const ProgramAttributes& attrs) -> GLProgram* {
    auto key = attrs.ProgramPermutationHash();
    if (!programs_.contains(key)) {
        auto sources = shader_lib_.GetShaderSource(attrs);
        if (sources.empty()) return nullptr;
        Logger::Log(LogLevel::Info, "Creating a new shader program {}", attrs.ProgramPermutationHash());
        programs_[key] = std::make_unique<GLProgram>(sources);
    }
    return programs_[key].get();
}

}