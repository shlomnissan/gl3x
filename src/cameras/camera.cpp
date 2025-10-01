/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/cameras/camera.hpp"

namespace gleam {

auto Camera::UpdateViewMatrix() -> void {
    if (ShouldUpdateWorldTransform()) {
        UpdateWorldTransform();
        this->view_matrix = Inverse(GetWorldTransform());
    }
}

auto Camera::GetFrustum() -> Frustum {
    return Frustum {projection_matrix * view_matrix};
}

auto Camera::LookAt(const Vector3& target) -> void {
    transform.LookAt(target, GetWorldPosition(), up);
}

}