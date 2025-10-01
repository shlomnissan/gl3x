/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/geometries/geometry.hpp"
#include "gleam/materials/material.hpp"
#include "gleam/math/frustum.hpp"
#include "gleam/nodes/node.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Internal base for anything renderable.
 *
 * Not part of the public API. Provides the minimal interface
 * needed by the renderer (geometry, material).
 *
 * @cond INTERNAL
 */
class GLEAM_EXPORT Renderable : public Node {
public:
    virtual ~Renderable() = default;

    [[nodiscard]] virtual auto GetGeometry() -> std::shared_ptr<Geometry> = 0;

    [[nodiscard]] virtual auto GetMaterial() -> std::shared_ptr<Material> = 0;

    [[nodiscard]] virtual auto BoundingBox() -> Box3;

    [[nodiscard]] virtual auto BoundingSphere() -> Sphere;

    [[nodiscard]] auto GetNodeType() const -> NodeType override {
        return NodeType::RenderableNode;
    }

    [[nodiscard]] auto IsRenderable() const -> bool override { return true; }

    [[nodiscard]] static auto CanRender(Renderable* r) -> bool;

    [[nodiscard]] static auto InFrustum(Renderable* r, const Frustum& frustum) -> bool;

    [[nodiscard]] static auto IsMeshType(Renderable* r) -> bool;

protected:
    Renderable() = default;
};
/// @endcond

}
