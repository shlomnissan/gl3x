/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/camera.hpp"

namespace gleam {

auto Camera::UpdateViewTransform() -> void {
    if (ShouldUpdateWorldTransform()) {
        UpdateWorldTransform();
        this->view_transform = Inverse(GetWorldTransform());
    }
}

auto Camera::LookAt(const Vector3& target) -> void {
    const auto position = GetWorldPosition();
    transform.LookAt(position, target, up);
}

}