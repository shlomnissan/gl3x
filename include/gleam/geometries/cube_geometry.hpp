/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/geometries/geometry.hpp"
#include "gleam/math/vector3.hpp"

#include <memory>

namespace gleam {

class GLEAM_EXPORT CubeGeometry : public Geometry {
public:
    struct Parameters {
        float width {1.0f};
        float height {1.0f};
        float depth {1.0f};
        unsigned width_segments {1};
        unsigned height_segments {1};
        unsigned depth_segments {1};
    };

    explicit CubeGeometry(const Parameters& params);

    [[nodiscard]] static auto Create() {
        return std::make_shared<CubeGeometry>(Parameters {});
    }

    [[nodiscard]] static auto Create(const Parameters& params){
        return std::make_shared<CubeGeometry>(params);
    }

private:
    unsigned int vertex_counter_ {0};
};

}