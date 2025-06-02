/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"
#include "gleam/core/geometry.hpp"
#include "gleam/materials/material.hpp"
#include "gleam/nodes/node.hpp"

#include <memory>
#include <optional>

namespace gleam {

/**
 * @brief Class representing a mesh, which is a node in the scene with associated geometry and material.
 */
class GLEAM_EXPORT Mesh : public Node {
public:
    /// @brief The geometry associated with the mesh.
    std::shared_ptr<Geometry> geometry;

    /// @brief The material associated with the mesh.
    std::shared_ptr<Material> material;

    /**
     * @brief Constructs a Mesh object with the given geometry.
     *
     * @param geometry A shared pointer to the Geometry object to be associated with the mesh.
     * @param material A shared pointer to the Material object to be associated with the mesh.
     */
    Mesh(
        std::shared_ptr<Geometry> geometry,
        std::shared_ptr<Material> material
    );

    /**
     * @brief Creates a shared pointer to a Mesh object with the specified geometry.
     *
     * @param geometry A shared pointer to the Geometry object to be associated with the mesh.
     * @param material A shared pointer to the Material object to be associated with the mesh.
     * @return std::shared_ptr<Mesh> A shared pointer to the newly created Mesh object.
     */
    [[nodiscard]]
    static auto Create(
        std::shared_ptr<Geometry> geometry,
        std::shared_ptr<Material> material
    ) {
        return std::make_shared<Mesh>(geometry, material);
    }
};

}