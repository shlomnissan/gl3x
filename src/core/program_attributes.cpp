// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/program_attributes.hpp"

#include "engine/core/logger.hpp"
#include "engine/materials/materials.hpp"

#include "lights/light.hpp"

#include <bitset>

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

    for (auto weak_light : scene->Lights()) {
        if (auto light = weak_light.lock()) {
            switch (light->Type()) {
                case LightType::Ambient: /* noop */ break;
                case LightType::Directional: directional_lights++; break;
                case LightType::Point: point_lights++; break;
                case LightType::Spotlight: spot_lights++; break;
                default: Logger::Log(LogLevel::Error, "Unknown light type"); break;
            }
        }
    }
}

auto ProgramAttributes::MaterialPermutationHash() const -> std::string {
    auto attrs = std::bitset<2> {};
    attrs[0] = color;
    attrs[1] = texture_map;

    return fmt::format("{}_material|p{}", MaterialTypeToString(type), attrs.to_ulong());
}

}