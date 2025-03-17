// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/math/frustum.hpp"

namespace engine {

Frustum::Frustum(const Matrix4& projection) {
    SetWithViewProjection(projection);
}

auto Frustum::SetWithViewProjection(const Matrix4& projection) -> void {
    planes[0] = Plane {{
        projection(3, 0) + projection(0, 0),
        projection(3, 1) + projection(0, 1),
        projection(3, 2) + projection(0, 2)
    }, projection(3, 3) + projection(0, 3)};

    planes[1] = Plane {{
        projection(3, 0) - projection(0, 0),
        projection(3, 1) - projection(0, 1),
        projection(3, 2) - projection(0, 2)
    }, projection(3, 3) - projection(0, 3)};

    planes[2] = Plane {{
        projection(3, 0) + projection(1, 0),
        projection(3, 1) + projection(1, 1),
        projection(3, 2) + projection(1, 2)
    }, projection(3, 3) + projection(1, 3)};

    planes[3] = Plane {{
        projection(3, 0) - projection(1, 0),
        projection(3, 1) - projection(1, 1),
        projection(3, 2) - projection(1, 2)
    }, projection(3, 3) - projection(1, 3)};

    planes[4] = Plane {{
        projection(3, 0) + projection(2, 0),
        projection(3, 1) + projection(2, 1),
        projection(3, 2) + projection(2, 2)
    }, projection(3, 3) + projection(2, 3)};

    planes[5] = Plane {{
        projection(3, 0) - projection(2, 0),
        projection(3, 1) - projection(2, 1),
        projection(3, 2) - projection(2, 2)
    }, projection(3, 3) - projection(2, 3)};

    for (auto& p : planes) p.Normalize();
}

auto Frustum::ContainsPoint(const Vector3& point) const -> bool {
    for (const auto& plane : planes) {
        if (plane.DistanceToPoint(point) < 0) {
            return false;
        }
    }
    return true;
}

auto Frustum::IntersectsWithBox3(const Box3& box) const -> bool {
    auto v = Vector3::Zero();
    for (const auto& plane : planes) {
        v.x = plane.normal.x > 0 ? box.max.x : box.min.x;
        v.y = plane.normal.y > 0 ? box.max.y : box.min.y;
        v.z = plane.normal.z > 0 ? box.max.z : box.min.z;

        if (plane.DistanceToPoint(v) < 0) {
            return false;
        }
    }
    return true;
}

auto Frustum::IntersectsWithSphere(const Sphere& sphere) const -> bool {
    for (const auto& plane : planes) {
        const auto distance = plane.DistanceToPoint(sphere.center);
        if (distance < -sphere.radius) {
            return false;
        }
    }
    return true;
}

}