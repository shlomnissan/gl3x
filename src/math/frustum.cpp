// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/math/frustum.hpp"

namespace engine {

Frustum::Frustum(const Matrix4& projection) {
    // TODO: implement
}

auto Frustum::ContainsPoint(const Vector3& point) const -> bool {
    // TODO: implement
    return false;
}

auto Frustum::IntersectsWithBox3(const Box3& box) const -> bool {
    // TODO: implement
    return false;
}

auto Frustum::IntersectsWithSphere(const Sphere& sphere) const -> bool {
    // TODO: implement
    return false;
}

}