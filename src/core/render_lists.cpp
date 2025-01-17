// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "core/render_lists.hpp"

namespace engine {

auto RenderLists::ProcessScene(Scene* scene) -> void {
    Reset();

    // TODO: process scene.
}

auto RenderLists::Reset() -> void {
    opaque_.clear();
    transparent_.clear();
    lights_.clear();
}

}