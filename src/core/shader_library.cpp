// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/shader_library.hpp"
#include "core/logger.hpp"

#include "engine/materials/flat_material.hpp"
#include "shaders/include/flat_material_vert.h"
#include "shaders/include/flat_material_frag.h"

#include "engine/materials/phong_material.hpp"
#include "shaders/include/phong_material_vert.h"
#include "shaders/include/phong_material_frag.h"

namespace engine {

auto ShaderLibrary::GetShaderSource(Material* material) -> std::vector<ShaderInfo> {
    using enum MaterialType;

    switch(material->Type()) {
        case kFlatMaterial:
            return {
                {ShaderType::kVertexShader, _SHADER_flat_material_vert},
                {ShaderType::kFragmentShader, _SHADER_flat_material_frag}
            };
        break;
        case kPhongMaterial:
            return {
                {ShaderType::kVertexShader, _SHADER_phong_material_vert},
                {ShaderType::kFragmentShader, _SHADER_phong_material_frag}
            };
        break;
        default:
            LogError("Shader source not found for unknown material type");
    }

    return {};
}

}