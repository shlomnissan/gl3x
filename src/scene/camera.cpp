// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/camera.hpp"

namespace engine {

auto Camera::UpdateTransforms() -> void {
    const auto view_needs_update = ShouldUpdateWorldTransform();
    Node::UpdateTransforms();
    if (view_needs_update) {
        this->view_transform = Transform { Inverse(world_transform.Get()) };
    }
}

}