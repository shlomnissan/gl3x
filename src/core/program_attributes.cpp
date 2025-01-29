// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "core/program_attributes.hpp"

#include "engine/lights/ambient_light.hpp"
#include "engine/lights/directional_light.hpp"
#include "engine/lights/point_light.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/materials/phong_material.hpp"
#include "engine/materials/shader_material.hpp"

#include "utilities/logger.hpp"

#include <array>

#include <fmt/format.h>

namespace engine {

ProgramAttributes::ProgramAttributes(const Material* material, const RenderLists* render_lists, const Scene* scene) {
    type = material->Type();

    if (type == MaterialType::FlatMaterial) {
        auto m = material->As<FlatMaterial>();
        texture_map = m->texture_map != nullptr;
    }

    if (type == MaterialType::PhongMaterial) {
        auto m = material->As<PhongMaterial>();
        lights = !render_lists->Lights().empty();
        texture_map = m->texture_map != nullptr;
    }

    if (type == MaterialType::ShaderMaterial) {
        auto m = material->As<ShaderMaterial>();
        vertex_shader = m->vertex_shader_;
        fragment_shader = m->fragment_shader_;
    }

    two_sided = material->two_sided;

    if (material->fog && scene->fog != nullptr) {
        if (scene->fog->Type() == FogType::LinearFog) {
            linear_fog = true;
        }
        if (scene->fog->Type() == FogType::ExponentialFog) {
            exponential_fog = true;
        }
    }

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
    auto attrs = std::array<int, 7> {
        directional_lights,
        exponential_fog ? 1 : 0,
        linear_fog ? 1 : 0,
        point_lights,
        spot_lights,
        texture_map ? 1 : 0,
        two_sided ? 1 : 0,
    };

    return fmt::format(
        "{}_material|p{}",
        Material::TypeToString(type),
        fmt::join(attrs, "")
    );
}

}