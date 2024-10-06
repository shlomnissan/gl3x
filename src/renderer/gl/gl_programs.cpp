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
    if (!programs_.contains(mesh->GetMaterial()->Type())) {
        auto material = mesh->GetMaterial();
        auto program = std::unique_ptr<GLProgram>();

        if (material->Is<FlatMaterial>()) {
            program = std::make_unique<GLProgram>(std::vector<GLShaderInfo>{
                {GLShaderType::kVertexShader, _SHADER_flat_material_vert},
                {GLShaderType::kFragmentShader, _SHADER_flat_material_frag}
            });
        }

        if (material->Is<PhongMaterial>()) {
            program = std::make_unique<GLProgram>(std::vector<GLShaderInfo>{
                {GLShaderType::kVertexShader, _SHADER_phong_material_vert},
                {GLShaderType::kFragmentShader, _SHADER_phong_material_frag}
            });
        }

        programs_[mesh->GetMaterial()->Type()] = std::move(program);
    }
    return programs_[mesh->GetMaterial()->Type()].get();
}

}