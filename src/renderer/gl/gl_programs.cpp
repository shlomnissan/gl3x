/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "renderer/gl/gl_programs.hpp"

#include "utilities/logger.hpp"

#include <vector>

namespace gleam {

auto GLPrograms::GetProgram(const ProgramAttributes& attrs) -> GLProgram* {
    const auto& key = attrs.key;
    if (!programs_.contains(key)) {
        auto sources = shader_lib_.GetShaderSource(attrs);
        if (sources.empty()) {
            return nullptr;
        }

        programs_[key] = std::make_unique<GLProgram>(sources);

        Logger::Log(
            LogLevel::Info,
            "Created a new shader program {}:{}",
            key, Material::TypeToString(attrs.type)
        );

    }
    return programs_[key].get();
}

}