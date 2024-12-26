// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <vector>

#include <engine/nodes.hpp>

#include "geometries/example_plane_geometry.hpp"
#include "geometries/example_sphere_geometry.hpp"
#include "lights/example_directional_light.hpp"
#include "lights/example_point_light.hpp"
#include "lights/example_spot_light.hpp"
#include "materials/example_flat_material.hpp"
#include "materials/example_phong_material.hpp"

static const auto examples = std::vector {
    "Flat Material",
    "Phong Material",
    "",
    "Directional Light",
    "Point Light",
    "Spot Light",
    "",
    "Plane Geometry",
    "Sphere Geometry",
};