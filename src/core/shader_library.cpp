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
#include "shaders/snippets/headers/vert_global_params_glsl.h"
#include "shaders/snippets/headers/vert_main_varyings_glsl.h"
#include "shaders/snippets/headers/frag_global_fog_glsl.h"
#include "shaders/snippets/headers/frag_global_params_glsl.h"
#include "shaders/snippets/headers/frag_main_normal_glsl.h"

#include <format>
#include <unordered_map>

namespace engine {

auto ShaderLibrary::GetShaderSource(const ProgramAttributes& attrs) const -> std::vector<ShaderInfo> {
    if (attrs.type == MaterialType::FlatMaterial) {
        return {{
            ShaderType::kVertexShader,
            ProcessShader(attrs, _SHADER_flat_material_vert)
        }, {
            ShaderType::kFragmentShader,
            ProcessShader(attrs, _SHADER_flat_material_frag)
        }};
    }

    if (attrs.type == MaterialType::PhongMaterial) {
        return {{
            ShaderType::kVertexShader,
            ProcessShader(attrs, _SHADER_phong_material_vert)
        }, {
            ShaderType::kFragmentShader,
            ProcessShader(attrs, _SHADER_phong_material_frag)
        }};
    }

    if (attrs.type == MaterialType::ShaderMaterial) {
        return {{
            ShaderType::kVertexShader,
            ProcessShader(attrs, attrs.vertex_shader)
        }, {
            ShaderType::kFragmentShader,
            ProcessShader(attrs, attrs.fragment_shader)
        }};
    }

    Logger::Log(
        LogLevel::Error,
        "Shader source not found for unknown material {}_material",
        Material::TypeToString(attrs.type)
    );

    return {};
}

auto ShaderLibrary::ProcessShader(
    const ProgramAttributes& attrs,
    std::string_view source
) const -> std::string {
    auto output = std::string {source};
    InjectAttributes(attrs, output);
    ResolveIncludes(output);
    return output;
}

auto ShaderLibrary::InjectAttributes(
    const ProgramAttributes& attrs,
    std::string& source
) const -> void {
    auto features = std::string {};

    if (attrs.color) features += "#define USE_COLOR\n";
    if (attrs.exponential_fog) features += "#define USE_FOG\n#define USE_EXPONENTIAL_FOG\n";
    if (attrs.linear_fog) features += "#define USE_FOG\n#define USE_LINEAR_FOG\n";
    if (attrs.texture_map) features += "#define USE_TEXTURE_MAP\n";
    if (attrs.two_sided) features += "#define USE_TWO_SIDED\n";
    if (attrs.flat_shaded) features += "#define USE_FLAT_SHADED\n";

    features += std::format("#define NUM_DIR_LIGHTS {}\n", attrs.directional_lights);
    features += std::format("#define NUM_POINT_LIGHTS {}\n", attrs.point_lights);
    features += std::format("#define NUM_SPOT_LIGHTS {}\n", attrs.spot_lights);

    auto token = std::string_view {"#pragma inject_attributes"};
    auto pos = source.find(token);
    if (pos == std::string::npos) {
        Logger::Log(
            LogLevel::Error,
            "The '#pragma inject_attributes' token is missing in program {}",
            Material::TypeToString(attrs.type)
        );
        return;
    }

    source.replace(pos, token.size(), features);
}

auto ShaderLibrary::ResolveIncludes(std::string& source) const -> void {
    static const std::unordered_map<std::string, std::string> include_map = {
        {"snippets/vert_global_params.glsl", _SNIPPET_vert_global_params},
        {"snippets/vert_main_varyings.glsl", _SNIPPET_vert_main_varyings},
        {"snippets/frag_global_params.glsl", _SNIPPET_frag_global_params},
        {"snippets/frag_global_fog.glsl", _SNIPPET_frag_global_fog},
        {"snippets/frag_main_normal.glsl", _SNIPPET_frag_main_normal}
    };

    for (const auto& [include, content] : include_map) {
        auto token = std::format("#include \"{}\"", include);
        auto pos = source.find(token);
        if (pos != std::string::npos) {
            source.replace(pos, token.size(), content);
        }
    }
}

}