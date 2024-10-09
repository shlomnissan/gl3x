// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/program_attributes.hpp"

namespace engine {

ProgramAttributes::ProgramAttributes(Material* material) {
    auto colorMaterial = dynamic_cast<MaterialWithColor*>(material);

    color = colorMaterial != nullptr;
}

}