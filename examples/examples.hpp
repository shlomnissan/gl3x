/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <vector>

#include <gleam/nodes.hpp>

#include "materials/example_unlit_material.hpp"
#include "materials/example_phong_material.hpp"
#include "materials/example_shader_material.hpp"
#include "lighting/example_directional_light.hpp"
#include "lighting/example_point_light.hpp"
#include "lighting/example_spot_light.hpp"
#include "rendering_effects/example_blending.hpp"
#include "rendering_effects/example_fog.hpp"
#include "scene_features/example_frustum_culling.hpp"
#include "scene_features/example_mesh_instancing.hpp"
#include "scene_features/example_model_loader.hpp"
#include "scene_features/example_primitives.hpp"
#include "scene_features/example_debug_visuals.hpp"
#include "animation/example_animated_transform.hpp"

static const auto examples = std::vector {
    "- Materials",
    "Unlit Material",
    "Phong Material",
    "Shader Material",
    "- Lights",
    "Directional Light",
    "Point Light",
    "Spot Light",
    "- Rendering Effects",
    "Transparency & Blending",
    "Fog Effect",
    "- Scene Features",
    "Frustum Culling",
    "Mesh Instancing",
    "Model Loader",
    "Primitives",
    "Debug Visuals",
    "- Animation",
    "Animated Transform"
};