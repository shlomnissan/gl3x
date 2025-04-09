// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "core/render_lists.hpp"

#include <ranges>
#include <limits>

namespace engine {

// Compare function for sorting meshes based on their z position.
const auto& compare = [](const auto& element) {
    if (const auto mesh = element.lock()) {
        return mesh->transform.GetPosition().z;
    }
    return std::numeric_limits<float>::max();
};

auto RenderLists::ProcessScene(Scene* scene) -> void {
    Reset();

    for (const auto& child : scene->Children()) {
        ProcessNode(child);
    }

    // Sort opaque meshes front-to-back to optimize depth buffer writes.
    std::ranges::sort(opaque_, std::ranges::greater {}, compare);

    // Sort transparent meshes back-to-front to ensure correct blending.
    std::ranges::sort(transparent_, std::ranges::less {}, compare);
}

auto RenderLists::ProcessNode(const std::shared_ptr<Node>& node) -> void {
    if (auto mesh = std::dynamic_pointer_cast<Mesh>(node)) {
        mesh->material->transparent ?
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