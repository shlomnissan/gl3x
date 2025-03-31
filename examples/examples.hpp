// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <vector>

#include <engine/nodes.hpp>

#include "debug/frustum_culling_debug.hpp"
#include "debug/lerp_animation_debug.hpp"
#include "effects/example_blending.hpp"
#include "effects/example_fog.hpp"
#include "geometries/example_box_geometry.hpp"
#include "geometries/example_cone_geometry.hpp"
#include "geometries/example_cylinder_geometry.hpp"
#include "geometries/example_plane_geometry.hpp"
#include "geometries/example_sphere_geometry.hpp"
#include "lights/example_directional_light.hpp"
#include "lights/example_point_light.hpp"
#include "lights/example_spot_light.hpp"
#include "materials/example_flat_material.hpp"
#include "materials/example_phong_material.hpp"
#include "materials/example_shader_material.hpp"

static const auto examples = std::vector {
    "Flat Material",
    "Phong Material",
    "Shader Material",
    "",
    "Directional Light",
    "Point Light",
    "Spot Light",
    "",
    "Box Geometry",
    "Cone Geometry",
    "Cylinder Geometry",
    "Plane Geometry",
    "Sphere Geometry",
    "",
    "Blending Effect",
    "Fog Effect",
    "",
    "Frustum Culling Debug",
    "Lerp Animation Debug"
};