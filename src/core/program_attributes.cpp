// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/program_attributes.hpp"

#include "engine/core/logger.hpp"
#include "engine/lights/ambient_light.hpp"
#include "engine/lights/directional_light.hpp"
#include "engine/lights/point_light.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/materials/phong_material.hpp"

#include <array>

#include <fmt/format.h>

namespace engine {

ProgramAttributes::ProgramAttributes(const Material* material, const Scene* scene) {
    type = material->Type();

    if (type == MaterialType::kFlatMaterial) {
        color = true;
        auto m = material->As<FlatMaterial>();
        texture_map = m->texture_map != nullptr;
    }

    if (type == MaterialType::kPhongMaterial) {
        color = true;
        lights = !scene->Lights().empty();
        auto m = material->As<PhongMaterial>();
        texture_map = m->texture_map != nullptr;
    }

    fog = scene->fog.has_value() && material->fog;

    for (auto weak_light : scene->Lights()) {
        if (auto light = weak_light.lock()) {
            using enum LightType;
            switch (light->Type()) {
                case Ambient: /* noop */ break;
                case Directional: directional_lights++; break;
                case Point: point_lights++; break;
                case Spot: spot_lights++; break;
                default: Logger::Log(LogLevel::Error, "Unknown light type"); break;
            }
        }
    }
}

auto ProgramAttributes::ProgramPermutationHash() const -> std::string {
    auto attrs = std::array<int, 6> {
        color ? 1 : 0,
        texture_map ? 1 : 0,
        fog ? 1 : 0,
        directional_lights,
        point_lights,
        spot_lights
    };

    return fmt::format(
        "{}_material|p{}",
        MaterialTypeToString(type),
        fmt::join(attrs, "")
    );
}

}