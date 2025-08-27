/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/geometries/geometry.hpp"
#include "gleam/materials/material.hpp"
#include "gleam/nodes/node.hpp"

#include <memory>

namespace gleam {

/**
 * @brief A sprite is a plane that always faces towards the camera.
 *
 * `Sprite` is a lightweight renderable commonly used for UI elements, particles,
 * text rendering, etc. It draws a camera-facing quad using the assigned material.
 *
 * @ingroup NodesGroup
 */
class GLEAM_EXPORT Sprite : public Node {
public:
    /**
     * @brief Constructs a sprite with an optional material.
     *
     * If @p material is null, a new instance of SpriteMaterial will be created.
     *
     * @param material Material used to render the sprite (may be null).
     */
    Sprite(std::shared_ptr<Material> material);

    /**
     * @brief Creates a shared pointer to a Sprite object.
     *
     * @return std::shared_ptr<Sprite>
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<Sprite>(nullptr);
    }

    /**
     * @brief Creates a shared pointer to a Sprite object with material.
     *
     * @param material Shared pointer to a SpriteMaterial instance.
     * @return std::shared_ptr<Sprite>
     */
    [[nodiscard]] static auto Create(std::shared_ptr<Material> material) {
        return std::make_shared<Sprite>(material);
    }

    /**
     * @brief Returns node type.
     *
     * @return NodeType::SpriteNode
     */
    [[nodiscard]] auto GetNodeType() const -> NodeType override {
        return NodeType::SpriteNode;
    }

    /**
     * @brief Sets the material used to render the sprite.
     *
     * @param material Shared pointer to a SpriteMaterial instance.
     */
    auto SetMaterial(std::shared_ptr<Material> material) { material_ = material; }

    /**
     * @brief Returns the material associated with the sprite.
     *
     * @return Shared pointer to the current material.
     */
    auto GetMaterial() { return material_; }

private:
    /// @cond INTERNAL
    std::shared_ptr<Geometry> geometry_;
    /// @endcond

    /// @brief Material used to render the sprite.
    std::shared_ptr<Material> material_;
};

}