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
 * auto geometry = gleam::BoxGeometry::Create();
 * auto material = gleam::UnlitMaterial::Create(0x00FFAA);
 * auto mesh = gleam::Mesh::Create(geometry, material);
 * my_scene->Add(mesh);
 * @endcode
 *
 * @ingroup NodesGroup
 */
class GLEAM_EXPORT Mesh : public Node {
public:
    /**
     * @brief Constructs a mesh instance with the given geometry and material.
     *
     * @param geometry Shared pointer to a geometry instance.
     * @param material Shared pointer to a material instance.
     */
    Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material)
      : geometry_(geometry), material_(material) {}

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

    /**
     * @brief Sets the geometry used to render this mesh.
     *
     * @param geometry Shared pointer to the new geometry.
     */
    auto SetGeometry(std::shared_ptr<Geometry> geometry) -> void;

     /**
     * @brief Sets the material used to render this mesh.
     *
     * @param material Shared pointer to the new material.
     */
    auto SetMaterial(std::shared_ptr<Material> material) { material_ = material; }

    /**
     * @brief Returns the geometry associated with this mesh.
     *
     * @return Shared pointer to the current geometry.
     */
    [[nodiscard]] auto GetGeometry() { return geometry_; }

    /**
     * @brief Returns the wireframe version of the mesh geometry.
     *
     * @return Shared pointer to the wireframe geometry.
     */
    [[nodiscard]] auto GetWireframeGeometry() -> std::shared_ptr<Geometry>;

    /**
     * @brief Returns the material associated with this mesh.
     *
     * @return Shared pointer to the current material.
     */
    [[nodiscard]] auto GetMaterial() { return material_; }

    /**
     * @brief Returns the mesh's bounding box.
     */
    [[nodiscard]] virtual auto BoundingBox() -> Box3;

    /**
     * @brief Returns the mesh's bounding sphere.
     */
    [[nodiscard]] virtual auto BoundingSphere() -> Sphere;

private:
    /// @brief Geometry data used for rendering this mesh.
    std::shared_ptr<Geometry> geometry_;

    /// @brief Wireframe geometry used for debug or line-based rendering.
    std::shared_ptr<Geometry> wireframe_geometry_;

    /// @brief Material that controls how the mesh is shaded.
    std::shared_ptr<Material> material_;
};

}