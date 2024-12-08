// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/core/geometry.hpp"
#include "engine/nodes/node.hpp"

#include "materials/material.hpp"

#include <memory>

namespace engine {

/**
 * @brief Class representing a mesh, which is a node in the scene with associated geometry and material.
 */
class Mesh : public Node {
public:
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
     * @brief Accessor method that returns a pointer to the underlying `Geometry` object.
     *
     * @return A pointer to the `Geometry` object as a `const` pointer.
     */
    auto GetGeometry() -> Geometry* { return geometry_.get(); }

    /**
     * @brief Accessor method that returns a pointer to the associated `Material` object.
     *
     * @return A raw pointer to the `Material` object, or nullptr if no material is set.
     */
    auto GetMaterial() -> Material* { return material_.get(); }

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

private:
    /// @brief The geometry associated with the mesh.
    std::shared_ptr<Geometry> geometry_;
    /// @brief The material associated with the mesh.
    std::shared_ptr<Material> material_;
};

}