// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/program_attributes.hpp"

#include "engine/core/logger.hpp"
#include "engine/materials.hpp"

#include "lights/light.hpp"

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

    for (auto weak_light : scene->Lights()) {
        if (auto light = weak_light.lock()) {
            using enum LightType;
            switch (light->Type()) {
                case Ambient: /* noop */ break;
                case Directional: directional_lights++; break;
                case Point: point_lights++; break;
                case Spotlight: spot_lights++; break;
                default: Logger::Log(LogLevel::Error, "Unknown light type"); break;
            }
        }
    }
}

auto ProgramAttributes::ProgramPermutationHash() const -> std::string {
    auto attrs = std::array<int, 5> {};
    attrs[0] = color ? 1 : 0;
    attrs[1] = texture_map ? 1 : 0;
    attrs[2] = directional_lights;
    attrs[3] = point_lights;
    attrs[4] = spot_lights;

    return fmt::format("{}_material|p{}", MaterialTypeToString(type), fmt::join(attrs, ""));
}

}