/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/geometries/geometry.hpp"
#include "gl3x/materials/material.hpp"
#include "gl3x/materials/sprite_material.hpp"
#include "gl3x/math/vector2.hpp"
#include "gl3x/nodes/renderable.hpp"

#include <memory>

namespace gl3x {

/**
 * @brief Billboarded quad that always faces the active camera.
 *
 * Sprite is a flat, unit-sized quad oriented toward the camera at all times.
 * It is usually textured (often with transparency) and exposes the minimal
 * Renderable interface so it can be submitted to the renderer.
 *
 * Common use cases include particles, labels, icons, and world-space markers.
 *
 * @code
 * auto MyNode::OnAttached(SharedContextPointer context) -> void override {
 *   context->texture_loader->LoadAsync(
 *     "assets/sprite.tex",
 *     [this](auto result) {
 *       if (result) {
 *         auto mat = gl3x::SpriteMaterial::Create();
 *         mat->albedo_map = result.value();
 *         auto sprite = Sprite::Create(mat);
 *         sprite->SetScale(0.5f);
 *         Add(sprite);
 *       } else {
 *         std::println(stderr, "{}", result.error());
 *       }
 *     }
 *   );
 * }
 * @endcode
 *
 * @ingroup NodesGroup
 */
class GL3X_EXPORT Sprite : public Renderable {
public:
    /**
     * @brief View-space rotation angle in radians applied to the sprite.
     */
    float rotation = 0.0f;

    /**
     * @brief Normalized anchor point inside the sprite.
     *
     * Defines the pivot used for placement and rotation of the sprite.
     *
     * - `(0.0f, 0.0f)` = lower-left corner of the sprite.
     * - `(0.5f, 0.5f)` = center of the sprite (default).
     * - `(1.0f, 1.0f)` = upper-right corner of the sprite.
     *
     * The sprite's world-space position corresponds to this anchor point.
     * Rotation is applied around this pivot.
     */
    Vector2 anchor = {0.5f, 0.5f};

    /**
     * @brief Constructs a sprite with an optional material.
     *
     * If @p material is null, a new instance of SpriteMaterial will be created.
     *
     * @param material Material used to render the sprite (may be null).
     */
    Sprite(std::shared_ptr<SpriteMaterial> material);

    /**
     * @brief Creates a shared pointer to a Sprite object with material.
     *
     * @param material Shared pointer to a sprite material.
     * @return std::shared_ptr<Sprite>
     */
    [[nodiscard]] static auto Create(std::shared_ptr<SpriteMaterial> material = nullptr) {
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
     * @brief Sets the material used to render the sprite.
     *
     * @param material Shared pointer to a sprite material.
     */
    auto SetMaterial(std::shared_ptr<SpriteMaterial> material) {
        material_ = material;
    }

private:
    /// @cond INTERNAL
    std::shared_ptr<Geometry> geometry_;
    static auto SharedGeometry() -> std::shared_ptr<Geometry>&;
    /// @endcond

    /// @brief Material used to render the sprite.
    std::shared_ptr<Material> material_;
};

}