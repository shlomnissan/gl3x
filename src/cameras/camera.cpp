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

}