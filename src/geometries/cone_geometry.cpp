/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gl3x/geometries/cone_geometry.hpp"

#include <cassert>

namespace gl3x {

ConeGeometry::ConeGeometry(const Parameters& params)
    : CylinderGeometry({
        .radius_top = 0.0f,
        .radius_bottom = params.radius,
        .height = params.height,
        .radial_segments = params.radial_segments,
        .height_segments = params.height_segments,
        .open_ended = params.open_ended
}) {
    SetName("cone geometry");
}

}