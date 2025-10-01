/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "core/program_attributes.hpp"
#include "core/shader_library.hpp"
#include "renderer/gl/gl_program.hpp"

#include <memory>
#include <unordered_map>

namespace gleam {

class GLPrograms {
public:
    auto GetProgram(const ProgramAttributes& attrs) -> GLProgram*;

private:
    ShaderLibrary shader_lib_;

    std::unordered_map<std::size_t, std::unique_ptr<GLProgram>> programs_ {};
};

}