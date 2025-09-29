/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "core/shader_library.hpp"

#include "gleam/materials/phong_material.hpp"
#include "gleam/materials/shader_material.hpp"
#include "gleam/materials/sprite_material.hpp"
#include "gleam/materials/unlit_material.hpp"

#include "utilities/logger.hpp"

#include "shaders/headers/phong_material_frag.h"
#include "shaders/headers/phong_material_vert.h"
#include "shaders/headers/sprite_material_frag.h"
#include "shaders/headers/sprite_material_vert.h"
#include "shaders/headers/unlit_material_frag.h"
#include "shaders/headers/unlit_material_vert.h"
#include "shaders/snippets/headers/frag_global_fog_glsl.h"
#include "shaders/snippets/headers/frag_global_params_glsl.h"
#include "shaders/snippets/headers/frag_main_normal_glsl.h"
#include "shaders/snippets/headers/utilities_glsl.h"
#include "shaders/snippets/headers/vert_global_params_glsl.h"
#include "shaders/snippets/headers/vert_main_varyings_glsl.h"

#include <unordered_map>

namespace gleam {

auto ShaderLibrary::GetShaderSource(const ProgramAttributes& attrs) const -> std::vector<ShaderInfo> {
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

    if (attrs.type == MaterialType::SpriteMaterial) {
        return {{
            ShaderType::kVertexShader,
            ProcessShader(attrs, _SHADER_sprite_material_vert)
        }, {
            ShaderType::kFragmentShader,
            ProcessShader(attrs, _SHADER_sprite_material_frag)
        }};
    }

    if (attrs.type == MaterialType::UnlitMaterial) {
        return {{
            ShaderType::kVertexShader,
            ProcessShader(attrs, _SHADER_unlit_material_vert)
        }, {
            ShaderType::kFragmentShader,
            ProcessShader(attrs, _SHADER_unlit_material_frag)
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

    if (attrs.alpha_map) features += "#define USE_ALPHA_MAP\n";
    if (attrs.normal_map) features += "#define USE_NORMAL_MAP\n";
    if (attrs.color) features += "#define USE_COLOR\n";
    if (attrs.flat_shaded) features += "#define USE_FLAT_SHADED\n";
    if (attrs.fog) features += "#define USE_FOG\n";
    if (attrs.instancing) features += "#define USE_INSTANCING\n";
    if (attrs.albedo_map) features += "#define USE_ALBEDO_MAP\n";
    if (attrs.two_sided) features += "#define USE_TWO_SIDED\n";
    if (attrs.vertex_color) features += "#define USE_VERTEX_COLOR\n";

    const auto lights = attrs.num_lights;
    features += "#define NUM_LIGHTS " + std::to_string(lights) + '\n';

    const auto token = std::string_view {"#pragma inject_attributes"};
    const auto pos = source.find(token);
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
        {"snippets/frag_global_fog.glsl", _SNIPPET_frag_global_fog},
        {"snippets/frag_global_params.glsl", _SNIPPET_frag_global_params},
        {"snippets/frag_main_normal.glsl", _SNIPPET_frag_main_normal},
        {"snippets/utilities.glsl", _SNIPPET_utilities},
        {"snippets/vert_global_params.glsl", _SNIPPET_vert_global_params},
        {"snippets/vert_main_varyings.glsl", _SNIPPET_vert_main_varyings}
    };

    for (const auto& [include, content] : include_map) {
        auto token = std::string {"#include \"" + include + "\""};
        auto pos = source.find(token);
        if (pos != std::string::npos) {
            source.replace(pos, token.size(), content);
        }
    }
}

}