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


auto RenderLists::ProcessScene(Scene* scene, Camera* camera) -> void {
    Reset();

    const auto frustum = camera->GetFrustum();
    for (const auto& child : scene->Children()) {
        ProcessNode(child.get(), frustum);
    }

    const auto c = camera->GetWorldPosition();
    const auto f = camera->ViewForward();
    const auto compare = [&](auto* renderable) {
        return Dot(renderable->GetWorldPosition() - c, f);
    };

    // Sort opaque renderables front-to-back to optimize depth buffer writes.
    std::ranges::stable_sort(opaque_, std::ranges::less {}, compare);

    // Sort transparent renderables back-to-front to ensure correct blending.
    std::ranges::stable_sort(transparent_, std::ranges::greater {}, compare);
}

auto RenderLists::ProcessNode(Node* node, const Frustum& frustum) -> void {
    const auto type = node->GetNodeType();

    if (node->IsRenderable()) {
        auto renderable = static_cast<Renderable*>(node);
        auto material = renderable->GetMaterial();

        if (!material->visible) return;
        if (!Renderable::CanRender(renderable)) return;
        if (!Renderable::IsInFrustum(renderable, frustum)) return;

        renderable->GetMaterial()->transparent
            ? transparent_.emplace_back(renderable)
            : opaque_.emplace_back(renderable);
    }

    if (type == NodeType::LightNode) {
        lights_.emplace_back(static_cast<Light*>(node));
    }

    for (const auto& child : node->Children()) {
        ProcessNode(child.get(), frustum);
    }
}

auto RenderLists::Reset() -> void {
    opaque_.clear();
    transparent_.clear();
    lights_.clear();
}

}