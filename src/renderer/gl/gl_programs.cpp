// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_programs.hpp"

#include "engine/materials/flat_material.hpp"
#include "shaders/include/flat_material_vert.h"
#include "shaders/include/flat_material_frag.h"

#include "engine/materials/phong_material.hpp"
#include "shaders/include/phong_material_vert.h"
#include "shaders/include/phong_material_frag.h"

#include "core/logger.hpp"

#include <vector>

#include <fmt/format.h>

namespace engine {

auto GLPrograms::GetProgram(Mesh* mesh) -> GLProgram* {
    auto material = mesh->GetMaterial();

    if (!programs_.contains(material->Type())) {
        programs_[material->Type()] = std::make_unique<GLProgram>(
            shader_lib_.GetShaderSource(material)
        );
    }
    return programs_[material->Type()].get();
}

}