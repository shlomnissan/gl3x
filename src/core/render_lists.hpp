// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/lights/light.hpp>
#include <engine/nodes/mesh.hpp>
#include <engine/nodes/node.hpp>
#include <engine/nodes/scene.hpp>

#include <memory>
#include <vector>

namespace engine {

class RenderLists {
public:
    auto ProcessScene(Scene* scene) -> void;

private:
    /// @brief A vector of weak pointers to opaque meshes in the scene.
    std::vector<std::weak_ptr<Mesh>> opaque_;

    /// @brief A vector of weak pointers to transparent meshes in the scene.
    std::vector<std::weak_ptr<Mesh>> transparent_;

    /// @brief A vector of weak pointers to lights in the scene.
    std::vector<std::weak_ptr<Light>> lights_;

    /**
     * @brief Processes nodes in the scene recursively.
     *
     * @param node The node to process.
     */
    auto ProcessNode(const std::shared_ptr<Node>& node) -> void;

    /**
     * @brief Resets the render lists.
     */
    auto Reset() -> void;
};

}