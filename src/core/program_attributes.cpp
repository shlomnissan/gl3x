// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/program_attributes.hpp"

#include <bitset>

#include <fmt/format.h>

namespace engine {

ProgramAttributes::ProgramAttributes(Material* material) {
    this->material = material;

    auto colorMaterial = material->As<MaterialWithColor>();
    color = (colorMaterial != nullptr);

    auto textureMapMaterial = material->As<MaterialWithTextureMap>();
    texture_map = (textureMapMaterial && textureMapMaterial->texture_map);
}

auto ProgramAttributes::PermutationKey() const -> std::string {
    auto attrs = std::bitset<2> {};
    attrs[0] = color;
    attrs[1] = texture_map;

    return fmt::format(
        "{}_material|v{:.1f}|p{}",
        ToString(material->Type()),
        material->Version(),
        attrs.to_ulong()
    );
}

}