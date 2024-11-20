// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/program_attributes.hpp"
#include "engine/materials/materials.hpp"

#include <bitset>

#include <fmt/format.h>

namespace engine {

ProgramAttributes::ProgramAttributes(Material* material) {
    type = material->Type();

    if (type == MaterialType::kFlatMaterial) {
        color = true;
        auto m = material->As<FlatMaterial>();
        texture_map = m->texture_map != nullptr;
    }

    if (type == MaterialType::kPhongMaterial) {
        color = true;
        auto m = material->As<PhongMaterial>();
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