// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/transform_2d.hpp"

namespace engine {

auto Transform2D::Get() const -> Matrix3 {
    return {
        1.0f, 0.0f, position.x,
        0.0f, 1.0f, position.y,
        0.0f, 0.0f, 1.0f
    };
}

}