// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "core/shader_library.hpp"

#include "engine/materials/flat_material.hpp"
#include "engine/materials/phong_material.hpp"
#include "engine/materials/shader_material.hpp"

#include "utilities/logger.hpp"

#include "shaders/headers/flat_material_vert.h"
#include "shaders/headers/flat_material_frag.h"
#include "shaders/headers/phong_material_vert.h"
#include "shaders/headers/phong_material_frag.h"

#include <fmt/format.h>

namespace engine {

auto ShaderLibrary::GetShaderSource(const ProgramAttributes& attrs) const -> std::vector<ShaderInfo> {
    if (attrs.type == MaterialType::FlatMaterial) {
        return {{
            ShaderType::kVertexShader,
            InjectAttributes(attrs, _SHADER_flat_material_vert)
        }, {
            ShaderType::kFragmentShader,
            InjectAttributes(attrs, _SHADER_flat_material_frag)
        }};
    }

    if (attrs.type == MaterialType::PhongMaterial) {
        return {{
            ShaderType::kVertexShader,
            InjectAttributes(attrs, _SHADER_phong_material_vert)
        }, {
            ShaderType::kFragmentShader,
            InjectAttributes(attrs, _SHADER_phong_material_frag)
        }};
    }

    if (attrs.type == MaterialType::ShaderMaterial) {
        return {{
            ShaderType::kVertexShader,
            InjectAttributes(attrs, attrs.vertex_shader)
        }, {
            ShaderType::kFragmentShader,
            InjectAttributes(attrs, attrs.fragment_shader)
        }};
    }

    Logger::Log(
        LogLevel::Error,
        "Shader source not found for unknown material {}_material",
        Material::TypeToString(attrs.type)
    );

    return {};
}

auto ShaderLibrary::InjectAttributes(
    const ProgramAttributes& attrs,
    std::string_view source
) const -> std::string {
    auto features = std::string {};

    if (attrs.exponential_fog) features += "#define USE_FOG\n#define USE_EXPONENTIAL_FOG\n";
    if (attrs.linear_fog) features += "#define USE_FOG\n#define USE_LINEAR_FOG\n";
    if (attrs.texture_map) features += "#define USE_TEXTURE_MAP\n";
    if (attrs.two_sided) features += "#define USE_TWO_SIDED\n";

    features += fmt::format("#define NUM_DIR_LIGHTS {}\n", attrs.directional_lights);
    features += fmt::format("#define NUM_POINT_LIGHTS {}\n", attrs.point_lights);
    features += fmt::format("#define NUM_SPOT_LIGHTS {}\n", attrs.spot_lights);

    auto output = std::string {source};
    auto token = std::string_view {"#pragma inject_attributes"};
    auto pos = output.find(token);
    if (pos == std::string::npos) {
        Logger::Log(
            LogLevel::Error,
            "The '#pragma inject_attributes' token is missing in program {}",
            Material::TypeToString(attrs.type)
        );
        return output;
    }

    output.replace(pos, token.size(), features);

    return output;
}

}