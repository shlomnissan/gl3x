/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/cameras/camera.hpp"

namespace gleam {

auto Camera::SetViewTransform() -> void {
    if (ShouldUpdateWorldTransform()) {
        UpdateWorldTransform();
        this->view_transform = Inverse(GetWorldTransform());
    }
}

auto Camera::GetFrustum() -> Frustum {
    return Frustum {projection_transform * view_transform};
}

auto Camera::LookAt(const Vector3& target) -> void {
    transform.LookAt(target, GetWorldPosition(), up);
}

}