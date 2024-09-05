// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/camera.hpp"

namespace engine {

auto Camera::UpdateTransforms() -> void {
    const auto view_needs_update = Node::ShouldUpdateTransform();
    Node::UpdateTransforms();
    if (view_needs_update) {
        this->view_transform_ = engine::inverse(GetWorldTransform());
    }
}

}