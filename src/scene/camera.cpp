// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/camera.hpp"

namespace engine {

auto Camera::UpdateTransforms() -> void {
    if (ShouldUpdateWorldTransform()) {
        Node::UpdateTransforms(true, false);
        this->view_transform = Inverse(world_transform.Get());
    }
}

}