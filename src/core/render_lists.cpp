// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "core/render_lists.hpp"

namespace engine {

auto RenderLists::ProcessScene(Scene* scene) -> void {
    Reset();
    for (const auto& child : scene->Children()) {
        ProcessNode(child);
    }
}

auto RenderLists::ProcessNode(const std::shared_ptr<Node>& node) -> void {
    if (auto mesh = std::dynamic_pointer_cast<Mesh>(node)) {
        mesh->GetMaterial()->transparent ?
            transparent_.emplace_back(mesh) :
            opaque_.emplace_back(mesh);
    }

    if (auto light = std::dynamic_pointer_cast<Light>(node)) {
        lights_.emplace_back(light);
    }

    for (const auto& child : node->Children()) {
        ProcessNode(child);
    }
}

auto RenderLists::Reset() -> void {
    opaque_.clear();
    transparent_.clear();
    lights_.clear();
}

}