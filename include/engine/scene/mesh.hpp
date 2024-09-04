// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/core/geometry.hpp"
#include "engine/scene/node.hpp"

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
     */
    explicit Mesh(std::shared_ptr<Geometry> geometry);

    /**
     * @brief Creates a shared pointer to a Mesh object with the specified geometry.
     *
     * @param geometry A shared pointer to the Geometry object to be associated with the mesh.
     * @return std::shared_ptr<Mesh> A shared pointer to the newly created Mesh object.
     */
    [[nodiscard]]
    static auto Create(std::shared_ptr<Geometry> geometry) {
        return std::make_shared<Mesh>(geometry);
    }

private:
    /// @brief The geometry associated with the mesh.
    std::shared_ptr<Geometry> geometry_;
};

}