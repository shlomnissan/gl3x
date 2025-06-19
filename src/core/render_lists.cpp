/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "core/render_lists.hpp"

#include <ranges>
#include <limits>

namespace gleam {

// Compare function for sorting meshes based on their z position.
const auto& compare = [](auto* mesh) {
    return mesh->transform.GetPosition().z;
};

auto RenderLists::ProcessScene(Scene* scene) -> void {
    Reset();

    for (const auto& child : scene->Children()) {
        ProcessNode(child.get());
    }

    // Sort opaque meshes front-to-back to optimize depth buffer writes.
    std::ranges::sort(opaque_, std::ranges::greater {}, compare);

    // Sort transparent meshes back-to-front to ensure correct blending.
    std::ranges::sort(transparent_, std::ranges::less {}, compare);
}

auto RenderLists::ProcessNode(Node* node) -> void {
    const auto type = node->GetNodeType();
    if (type == NodeType::MeshNode) {
        auto mesh = static_cast<Mesh*>(node);
        mesh->material->transparent ?
            transparent_.emplace_back(mesh) :
            opaque_.emplace_back(mesh);
    }

    if (type == NodeType::LightNode) {
        lights_.emplace_back(static_cast<Light*>(node));
    }

    for (const auto& child : node->Children()) {
        ProcessNode(child.get());
    }
}

auto RenderLists::Reset() -> void {
    opaque_.clear();
    transparent_.clear();
    lights_.clear();
}

}