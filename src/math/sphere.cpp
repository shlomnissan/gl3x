// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/math/sphere.hpp"

namespace engine {

auto Sphere::Reset() -> void {
    center_ = Vector3::Zero();
    radius_ = -1.0f;
}

}