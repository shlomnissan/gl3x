// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/program_attributes.hpp"

#include <bitset>

#include <fmt/format.h>

namespace engine {

ProgramAttributes::ProgramAttributes(Material* material) {
    this->material = material;

    lights = material->supports_lights;

    auto colorMaterial = material->As<MaterialWithColor>();
    color = (colorMaterial != nullptr);

    auto textureMapMaterial = material->As<MaterialWithTextureMap>();
    texture_map = (textureMapMaterial && textureMapMaterial->texture_map);
}

auto ProgramAttributes::PermutationKey() const -> std::string {
    auto attrs = std::bitset<3> {};
    attrs[0] = color;
    attrs[1] = texture_map;
    attrs[2] = lights;

    return fmt::format(
        "{}_material|p{}",
        MaterialTypeToString(material->Type()),
        attrs.to_ulong()
    );
}

}