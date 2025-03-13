// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/math/frustum.hpp"

namespace engine {

Frustum::Frustum(const Matrix4& projection) {
    // left plane
    planes[0] = Plane {{
        projection(3, 0) - projection(0, 0),
        projection(3, 1) - projection(0, 1),
        projection(3, 2) - projection(0, 2)
    }, projection(3, 3) - projection(0, 3)};
    planes[0].Normalize();

    // right plane
    planes[1] = Plane {{
        projection(3, 0) + projection(0, 0),
        projection(3, 1) + projection(0, 1),
        projection(3, 2) + projection(0, 2)
    }, projection(3, 3) + projection(0, 3)};
    planes[1].Normalize();
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