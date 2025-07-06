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
 * @brief Renderable scene node composed of geometry and material.
 *
 * `Mesh` is a node that represents a visible object in the scene. It combines
 * a `Geometry` object, which defines the shape and structure of the mesh,
 * with a `Material` object, which defines its surface appearance and shading.
 *
 * Meshes are typically added to a scene to be rendered during each frame.
 * Both the geometry and material can be assigned directly at creation time,
 * or modified afterward.
 *
 * @code
 * auto geometry = gleam::CubeGeometry::Create();
 * auto material = gleam::FlatMaterial::Create(0x00FFAA);
 * auto mesh = gleam::Mesh::Create(geometry, material);
 * my_scene->Add(mesh);
 * @endcode
 *
 * @ingroup NodesGroup
 */
class GLEAM_EXPORT Mesh : public Node {
public:
    /// @brief Geometry data used for rendering this mesh.
    std::shared_ptr<Geometry> geometry;

    /// @brief Material that controls how the mesh is shaded.
    std::shared_ptr<Material> material;

    /**
     * @brief Constructs a mesh instance with the given geometry and material.
     *
     * @param geometry Shared pointer to a geometry instance.
     * @param material Shared pointer to a material instance.
     */
    Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material)
      : geometry(geometry), material(material) {}

    /**
     * @brief Creates a shared pointer to a Mesh object.
     *
     * @param geometry Shared pointer to a geometry instance.
     * @param material Shared pointer to a material instance.
     * @return std::shared_ptr<Mesh>
     */
    [[nodiscard]] static auto Create(
        std::shared_ptr<Geometry> geometry,
        std::shared_ptr<Material> material
    ) {
        return std::make_shared<Mesh>(geometry, material);
    }

    /**
     * @brief Returns node type.
     *
     * @return NodeType::MeshNode
     */
    [[nodiscard]] auto GetNodeType() const -> NodeType override {
        return NodeType::MeshNode;
    }
};

}