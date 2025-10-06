/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx_export.h"

#include "vglx/geometries/geometry.hpp"
#include "vglx/materials/material.hpp"
#include "vglx/nodes/renderable.hpp"

#include <memory>

namespace gl3x {

/**
 * @brief Renderable node that draws a Geometry with a Material.
 *
 * Mesh is a scene node that owns a geometry and a material and exposes them
 * through the Renderable interface so the renderer can process and draw it.
 *
 * An optional wireframe geometry can be provided for debug rendering.
 *
 * @code
 * auto geometry = gl3x::BoxGeometry::Create();
 * auto material = gl3x::UnlitMaterial::Create(0x00FFAA);
 * auto mesh = gl3x::Mesh::Create(geometry, material);
 * my_scene->Add(mesh);
 * @endcode
 *
 * @ingroup NodesGroup
 */
class VGLX_EXPORT Mesh : public Renderable {
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
     * @brief Returns the geometry associated with this mesh.
     *
     * @return Shared pointer to the current geometry.
     */
    [[nodiscard]] auto GetGeometry() -> std::shared_ptr<Geometry> override {
        return geometry_;
    }

    /**
     * @brief Returns the material associated with this mesh.
     *
     * @return Shared pointer to the current material.
     */
    [[nodiscard]] auto GetMaterial() -> std::shared_ptr<Material> override {
        return material_;
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
     * @brief Returns the wireframe version of the mesh geometry.
     *
     * @return Shared pointer to the wireframe geometry.
     */
    [[nodiscard]] auto GetWireframeGeometry() -> std::shared_ptr<Geometry>;

    /**
     * @brief Default destructor.
     */
    virtual ~Mesh() = default;

private:
    /// @brief Geometry data used for rendering this mesh.
    std::shared_ptr<Geometry> geometry_;

    /// @brief Wireframe geometry used for debug or line-based rendering.
    std::shared_ptr<Geometry> wireframe_geometry_;

    /// @brief Material that controls how the mesh is shaded.
    std::shared_ptr<Material> material_;
};

}