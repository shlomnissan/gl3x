// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "core/program_attributes.hpp"

#include "gleam/lights/ambient_light.hpp"
#include "gleam/lights/directional_light.hpp"
#include "gleam/lights/point_light.hpp"
#include "gleam/materials/flat_material.hpp"
#include "gleam/materials/phong_material.hpp"
#include "gleam/materials/shader_material.hpp"

#include "utilities/logger.hpp"

#include <array>
#include <format>
#include <string>

namespace gleam {

ProgramAttributes::ProgramAttributes(const Material* material, const RenderLists* render_lists, const Scene* scene) {
    type = material->Type();

    if (type == MaterialType::FlatMaterial) {
        auto m = material->As<FlatMaterial>();
        color = true;
        texture_map = m->texture_map != nullptr;
    }

    if (type == MaterialType::PhongMaterial) {
        auto m = material->As<PhongMaterial>();
        color = true;
        lights = !render_lists->Lights().empty();
        texture_map = m->texture_map != nullptr;
    }

    if (type == MaterialType::ShaderMaterial) {
        auto m = material->As<ShaderMaterial>();
        vertex_shader = m->vertex_shader_;
        fragment_shader = m->fragment_shader_;
    }

    flat_shaded = material->flat_shaded;
    fog = material->fog && scene->fog != nullptr;
    two_sided = material->two_sided;

    for (auto weak_light : render_lists->Lights()) {
        if (auto light = weak_light.lock()) {
            using enum LightType;
            switch (light->Type()) {
                case AmbientLight: /* noop */ break;
                case DirectionalLight: directional_lights++; break;
                case PointLight: point_lights++; break;
                case SpotLight: spot_lights++; break;
                default: Logger::Log(LogLevel::Error, "Unknown light type"); break;
            }
        }
    }
}

auto ProgramAttributes::ProgramPermutationHash() const -> std::string {
    auto attrs = std::array<int, 9> {
        color ? 1 : 0,
        directional_lights,
        flat_shaded ? 1 : 0,
        fog ? 1 : 0,
        point_lights,
        spot_lights,
        texture_map ? 1 : 0,
        two_sided ? 1 : 0,
    };

    auto attrs_str = std::string {};
    for (auto attr : attrs) attrs_str += std::to_string(attr);

    return std::format(
        "{}_material|p{}",
        Material::TypeToString(type),
        attrs_str
    );
}

}