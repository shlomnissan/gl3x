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
#include "gleam/materials/sprite_material.hpp"

#include "utilities/logger.hpp"

#include <cassert>

namespace gleam {

ProgramAttributes::ProgramAttributes(
    Renderable* renderable,
    const LightsCounter& lights,
    const Scene* scene
) {
    auto geometry = renderable->GetGeometry().get();
    auto material = renderable->GetMaterial().get();

    type = material->GetType();

    if (type == MaterialType::PhongMaterial) {
        auto m = static_cast<const PhongMaterial*>(material);
        color = true;
        albedo_map = m->albedo_map != nullptr;
        alpha_map = m->alpha_map != nullptr;
        normal_map = m->normal_map != nullptr;
    }

    if (type == MaterialType::ShaderMaterial) {
        auto m = static_cast<const ShaderMaterial*>(material);
        vertex_shader = m->vertex_shader_;
        fragment_shader = m->fragment_shader_;
    }

    if (type == MaterialType::SpriteMaterial) {
        auto m = static_cast<const SpriteMaterial*>(material);
        color = true;
        albedo_map = m->albedo_map != nullptr;
        alpha_map = m->alpha_map != nullptr;
    }

    if (type == MaterialType::UnlitMaterial) {
        auto m = static_cast<const UnlitMaterial*>(material);
        color = true;
        albedo_map = m->albedo_map != nullptr;
        alpha_map = m->alpha_map != nullptr;
    }

    flat_shaded = material->flat_shaded;
    fog = material->fog && scene->fog != nullptr;
    instancing = renderable->GetNodeType() == NodeType::InstancedMeshNode;
    num_lights = lights.directional + lights.point + lights.spot;
    two_sided = material->two_sided;
    vertex_color = geometry->HasAttribute(VertexAttributeType::Color);

    static_assert(std::to_underlying(MaterialType::Length) <= 15);

    key |= (std::to_underlying(type) & 0xF); // (0–15) → 4 bits
    key |= (color ? 1 : 0)  << 4; // 1 bit
    key |= (flat_shaded ? 1 : 0) << 9; // 1 bit
    key |= (fog ? 1 : 0) << 10; // 1 bit
    key |= (lights.directional & 0xF) << 5; // (0–15) → 4 bits
    key |= (lights.point & 0xF) << 11; // (0–15) → 4 bits
    key |= (lights.spot & 0xF) << 15; // (0–15) → 4 bits
    key |= (albedo_map ? 1 : 0) << 19; // 1 bit
    key |= (alpha_map ? 1 : 0) << 20; // 1 bit
    key |= (normal_map ? 1 : 0) << 21; // 1 bit
    key |= (two_sided ? 1 : 0) << 22; // 1 bit
    key |= (instancing ? 1 : 0) << 23; // 1 bit
    key |= (vertex_color ? 1 : 0) << 24; // 1 bit
}

}