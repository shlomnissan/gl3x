/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "core/program_attributes.hpp"

#include "gleam/lights/ambient_light.hpp"
#include "gleam/lights/directional_light.hpp"
#include "gleam/lights/point_light.hpp"
#include "gleam/materials/flat_material.hpp"
#include "gleam/materials/phong_material.hpp"
#include "gleam/materials/shader_material.hpp"

#include "utilities/logger.hpp"

namespace gleam {

ProgramAttributes::ProgramAttributes(const Material* material, const RenderLists* render_lists, const Scene* scene) {
    type = material->GetType();

    if (type == MaterialType::FlatMaterial) {
        auto m = static_cast<const FlatMaterial*>(material);
        color = true;
        texture_map = m->texture_map != nullptr;
    }

    if (type == MaterialType::PhongMaterial) {
        auto m = static_cast<const PhongMaterial*>(material);
        color = true;
        lights = !render_lists->Lights().empty();
        texture_map = m->texture_map != nullptr;
    }

    if (type == MaterialType::ShaderMaterial) {
        auto m = static_cast<const ShaderMaterial*>(material);
        vertex_shader = m->vertex_shader_;
        fragment_shader = m->fragment_shader_;
    }

    flat_shaded = material->flat_shaded;
    fog = material->fog && scene->fog != nullptr;
    two_sided = material->two_sided;

    for (auto light : render_lists->Lights()) {
        switch (light->GetType()) {
            case LightType::AmbientLight: /* noop */ break;
            case LightType::DirectionalLight: directional_lights++; break;
            case LightType::PointLight: point_lights++; break;
            case LightType::SpotLight: spot_lights++; break;
            default: Logger::Log(LogLevel::Error, "Unknown light type"); break;
        }
    }

    key |= std::to_underlying(type);          // 0–15 → 4 bits
    key |= (color         ? 1 : 0)  << 4;     // 1 bit
    key |= (directional_lights & 0xF) << 5;   // 0–10 → 4 bits
    key |= (flat_shaded   ? 1 : 0)  << 9;     // 1 bit
    key |= (fog           ? 1 : 0)  << 10;    // 1 bit
    key |= (point_lights  & 0xF)    << 11;    // 0–10 → 4 bits
    key |= (spot_lights   & 0xF)    << 15;    // 0–10 → 4 bits
    key |= (texture_map   ? 1 : 0)  << 19;    // 1 bit
    key |= (two_sided     ? 1 : 0)  << 20;    // 1 bit
}

}