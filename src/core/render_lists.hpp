/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/lights/light.hpp"
#include "gleam/nodes/mesh.hpp"
#include "gleam/nodes/node.hpp"
#include "gleam/nodes/scene.hpp"

#include <memory>
#include <span>
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
    [[nodiscard]] auto Opaque() const -> std::span<Mesh* const> {
        return opaque_;
    }

    /**
     * @brief Retrieves the list of transparent meshes in the scene.
     *
     * @return A vector of weak pointers to transparent meshes.
     */
    [[nodiscard]] auto Transparent() const -> std::span<Mesh* const> {
        return transparent_;
    }

    /**
     * @brief Retrieves the list of lights in the scene.
     *
     * @return A vector of weak pointers to lights.
     */
    [[nodiscard]] auto Lights() const -> std::span<Light* const> {
        return lights_;
    }

private:
    /// @brief A vector of weak pointers to opaque meshes in the scene.
    std::vector<Mesh*> opaque_;

    /// @brief A vector of weak pointers to transparent meshes in the scene.
    std::vector<Mesh*> transparent_;

    /// @brief A vector of weak pointers to lights in the scene.
    std::vector<Light*> lights_;

    /**
     * @brief Processes nodes in the scene recursively.
     *
     * @param node The node to process.
     */
    auto ProcessNode(Node*) -> void;

    /**
     * @brief Resets the render lists.
     */
    auto Reset() -> void;
};

}