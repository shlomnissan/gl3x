// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <gleam/lights/light.hpp>
#include <gleam/nodes/mesh.hpp>
#include <gleam/nodes/node.hpp>
#include <gleam/nodes/scene.hpp>

#include <memory>
#include <vector>

namespace gleam {

class RenderLists {
public:
    /**
     * @brief Processes the scene and generates render lists.
     *
     * @param scene The scene to process.
     */
    auto ProcessScene(Scene* scene) -> void;

    /**
     * @brief Retrieves the list of opaque meshes in the scene.
     *
     * @return A vector of weak pointers to opaque meshes.
     */
    [[nodiscard]] auto Opaque() const -> const std::vector<std::weak_ptr<Mesh>>& {
        return opaque_;
    }

    /**
     * @brief Retrieves the list of transparent meshes in the scene.
     *
     * @return A vector of weak pointers to transparent meshes.
     */
    [[nodiscard]] auto Transparent() const -> const std::vector<std::weak_ptr<Mesh>>& {
        return transparent_;
    }

    /**
     * @brief Retrieves the list of lights in the scene.
     *
     * @return A vector of weak pointers to lights.
     */
    [[nodiscard]] auto Lights() const -> const std::vector<std::weak_ptr<Light>>& {
        return lights_;
    }

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