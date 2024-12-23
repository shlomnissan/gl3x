// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <vector>

#include <engine/nodes.hpp>

#include "example_geometries_plane.hpp"
#include "example_lights_directional.hpp"
#include "example_lights_point.hpp"
#include "example_lights_spot.hpp"
#include "example_materials_flat.hpp"
#include "example_materials_phong.hpp"

static const auto examples = std::vector {
    "Flat Material",
    "Phong Material",
    "",
    "Directional Light",
    "Point Light",
    "Spot Light",
    "",
    "Plane Geometry",
};