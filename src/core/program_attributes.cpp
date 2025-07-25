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
#include "gleam/materials/unlit_material.hpp"
#include "gleam/materials/phong_material.hpp"
#include "gleam/materials/shader_material.hpp"

#include "utilities/logger.hpp"

namespace gleam {

ProgramAttributes::ProgramAttributes(const Material* material, const LightsCounter& lights, const Scene* scene) {
    type = material->GetType();

    if (type == MaterialType::UnlitMaterial) {
        auto m = static_cast<const UnlitMaterial*>(material);
        color = true;
        texture_map = m->texture_map != nullptr;
        alpha_map = m->alpha_map != nullptr;
    }

    if (type == MaterialType::PhongMaterial) {
        auto m = static_cast<const PhongMaterial*>(material);
        color = true;
        texture_map = m->texture_map != nullptr;
        alpha_map = m->alpha_map != nullptr;
    }

    if (type == MaterialType::ShaderMaterial) {
        auto m = static_cast<const ShaderMaterial*>(material);
        vertex_shader = m->vertex_shader_;
        fragment_shader = m->fragment_shader_;
    }

    flat_shaded = material->flat_shaded;
    fog = material->fog && scene->fog != nullptr;
    two_sided = material->two_sided;

    num_lights = lights.directional + lights.point + lights.spot;

    key |= std::to_underlying(type); // 0–15 → 4 bits
    key |= (color ? 1 : 0)  << 4; // 1 bit
    key |= (flat_shaded ? 1 : 0) << 9; // 1 bit
    key |= (fog ? 1 : 0) << 10; // 1 bit
    key |= (lights.directional & 0xF) << 5; // 0–10 → 4 bits
    key |= (lights.point & 0xF) << 11; // 0–10 → 4 bits
    key |= (lights.spot & 0xF) << 15; // 0–10 → 4 bits
    key |= (texture_map ? 1 : 0) << 19; // 1 bit
    key |= (alpha_map ? 1 : 0) << 20; // 1 bit
    key |= (two_sided ? 1 : 0) << 21; // 1 bit
}

}