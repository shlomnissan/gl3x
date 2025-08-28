/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/nodes/node.hpp"

#include <memory>

namespace gleam {

class Geometry;
class Material;

/**
 * @brief Internal base for anything renderable.
 *
 * Not part of the public API. Provides the minimal interface
 * needed by the renderer (geometry, material).
 *
 * @cond INTERNAL
 */
class Renderable : public Node {
public:
    virtual ~Renderable() = default;

    [[nodiscard]] virtual auto GetGeometry() const -> std::shared_ptr<Geometry> = 0;

    [[nodiscard]] virtual auto GetMaterial() const -> std::shared_ptr<Material> = 0;

    [[nodiscard]] auto GetNodeType() const -> NodeType override {
        return NodeType::RenderableNode;
    }

protected:
    Renderable() = default;
};
/// @endcond

}
