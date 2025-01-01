// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <vector>

#include <engine/nodes.hpp>

#include "geometries/example_box_geometry.hpp"
#include "geometries/example_cylinder_geometry.hpp"
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
    "Box Geometry",
    "Cylinder Geometry",
    "Plane Geometry",
    "Sphere Geometry",
};