// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/program_attributes.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/materials/phong_material.hpp"

#include <bitset>

#include <fmt/format.h>

namespace engine {

ProgramAttributes::ProgramAttributes(Material* material) {
    type = material->Type();

    if (auto m = material->As<FlatMaterial>()) {
        color = true;
        texture_map = m->texture_map != nullptr;
    }

    if (auto m = material->As<PhongMaterial>()) {
        color = true;
        lights = true;
        texture_map = m->texture_map != nullptr;
    }
}

auto ProgramAttributes::PermutationKey() const -> std::string {
    auto attrs = std::bitset<3> {};
    attrs[0] = color;
    attrs[1] = texture_map;
    attrs[2] = lights;

    return fmt::format("{}_material|p{}", MaterialTypeToString(type), attrs.to_ulong());
}

}