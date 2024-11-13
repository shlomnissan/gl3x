// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/shader_library.hpp"

#include "engine/core/logger.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/materials/phong_material.hpp"

#include "shaders/headers/flat_material_vert.h"
#include "shaders/headers/flat_material_frag.h"
#include "shaders/headers/phong_material_vert.h"
#include "shaders/headers/phong_material_frag.h"

namespace engine {

auto ShaderLibrary::GetShaderSource(const ProgramAttributes& attrs) -> std::vector<ShaderInfo> {
    auto material = attrs.material;

    if (material->Type() == MaterialType::kFlatMaterial) {
        return {{
            ShaderType::kVertexShader,
            InjectAttributes(attrs, _SHADER_flat_material_vert)
        }, {
            ShaderType::kFragmentShader,
            InjectAttributes(attrs, _SHADER_flat_material_frag
        )}};
    }

    if (material->Type() == MaterialType::kPhongMaterial) {
        return {{
            ShaderType::kVertexShader,
            InjectAttributes(attrs, _SHADER_phong_material_vert)
        }, {
            ShaderType::kFragmentShader,
            InjectAttributes(attrs, _SHADER_phong_material_frag
        )}};
    }

    Logger::Log(
        LogLevel::Error,
        "Shader source not found for unknown material {}_material",
        MaterialTypeToString(material->Type())
    );

    return {};
}

auto ShaderLibrary::InjectAttributes(
    const ProgramAttributes& attrs,
    std::string_view source
) -> std::string {
    auto material = attrs.material;
    auto features = std::string {};

    if (attrs.color) features += "#define USE_COLOR\n";
    if (attrs.texture_map) features += "#define USE_TEXTURE_MAP\n";

    auto output = std::string {source};
    auto token = std::string_view {"#pragma inject_attributes"};
    auto pos = output.find(token);
    if (pos == std::string::npos) {
        Logger::Log(
            LogLevel::Error,
            "The '#pragma inject_attributes' token is missing in program {}",
            *material
        );
        return output;
    }

    output.replace(pos, token.size(), features);

    return output;
}

}