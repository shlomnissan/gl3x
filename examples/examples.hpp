// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <vector>

#include <engine/nodes.hpp>

#include "example_light_directional.hpp"
#include "example_material_flat.hpp"
#include "example_material_phong.hpp"

static const auto examples = std::vector {
    "Flat Material",
    "Phong Material",
    "",
    "Directional Light"
};