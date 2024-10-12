// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/program_attributes.hpp"

namespace engine {

ProgramAttributes::ProgramAttributes(Material* material) {
    this->material = material;

    auto colorMaterial = material->As<MaterialWithColor>();
    color = (colorMaterial != nullptr);

    auto textureMapMaterial = material->As<MaterialWithTextureMap>();
    texture_map = (textureMapMaterial && textureMapMaterial->texture_map);
}

}