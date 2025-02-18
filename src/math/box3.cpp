// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/math/box3.hpp"

#include <limits>

namespace engine {

Box3::Box3()
    : min_(std::numeric_limits<float>::max()),
      max_(std::numeric_limits<float>::lowest()) {}

Box3::Box3(const Vector3& v_min, const Vector3& v_max)
    : min_(v_min),
      max_(v_max) {}

}