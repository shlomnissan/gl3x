// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/core/geometry.hpp"
#include "engine/materials/material.hpp"
#include "engine/nodes/node.hpp"

#include <memory>
#include <optional>

namespace engine {

/**
 * @brief Class representing a mesh, which is a node in the scene with associated geometry and material.
 */
class ENGINE_EXPORT Mesh : public Node {
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