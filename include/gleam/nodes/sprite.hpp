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
#include "gleam/nodes/renderable.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Camera-facing quad renderable for billboards, UI, and text.
 *
 * Sprite is a unit quad that always faces the active camera. It exposes
 * the minimal Renderable interface so the renderer can draw it.
 *
 * Sprites are commonly used for particles, icons, and text glyphs. Geometry is
 * shared across all sprites and treated as read-only; per-sprite appearance is
 * controlled via the material.
 *
 * @ingroup NodesGroup
 */
class GLEAM_EXPORT Sprite : public Renderable {
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
     * @brief Creates a shared pointer to a Sprite object with material.
     *
     * @param material Shared pointer to a SpriteMaterial instance.
     * @return std::shared_ptr<Sprite>
     */
    [[nodiscard]] static auto Create(std::shared_ptr<Material> material = nullptr) {
        return std::make_shared<Sprite>(material);
    }

    /// @cond INTERNAL
    [[nodiscard]] auto GetGeometry() -> std::shared_ptr<Geometry> override {
        return geometry_;
    }
    /// @endcond

    /**
     * @brief Returns the material associated with the sprite.
     *
     * @return Shared pointer to the current material.
     */
    [[nodiscard]] auto GetMaterial() -> std::shared_ptr<Material> override {
        return material_;
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

private:
    /// @cond INTERNAL
    std::shared_ptr<Geometry> geometry_;
    /// @endcond

    /// @brief Material used to render the sprite.
    std::shared_ptr<Material> material_;
};

}