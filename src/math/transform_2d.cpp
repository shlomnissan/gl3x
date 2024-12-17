// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/transform_2d.hpp"

#include <cmath>

namespace engine {

auto Transform2D::Get() const -> Matrix3 {
    // This transform is currently used for UV transformations.
    // 2D screen space transformations will require minor adjustments.
    const auto rc = std::cos(rotation);
    const auto rs = std::sin(rotation);
    const auto ts = -scale.x * (rc * center.x + rs * center.y) + center.x + position.x;
    const auto ty = -scale.y * (-rs * center.x + rc * center.y) + center.y + position.y;
    return {
        scale.x * rc, scale.x * rs, ts,
        -scale.y * rs, scale.y * rc, ty,
        0.0f, 0.0f, 1.0f
    };
}

}