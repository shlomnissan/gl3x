// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "gleam/nodes/camera.hpp"

namespace engine {

auto Camera::UpdateViewTransform() -> void {
    if (ShouldUpdateWorldTransform()) {
        UpdateWorldTransform();
        this->view_transform = Inverse(GetWorldTransform());
    }
}

}