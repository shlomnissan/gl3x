// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/core/geometry.hpp"
#include "engine/scene/node.hpp"
#include "engine/textures/texture_2d.hpp"

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
     * @param texture A shared pointer to an optional Texture2D object to be associated with the mesh.
     */
    Mesh(
        std::shared_ptr<Geometry> geometry,
        std::shared_ptr<Texture2D> texture = nullptr
    );

    /**
     * @brief Accessor method that returns a pointer to the underlying `Geometry` object.
     *
     * @return A pointer to the `Geometry` object as a `const` pointer.
     */
    auto GetGeometry() -> Geometry* { return geometry_.get(); }

    /**
     * @brief Accessor method that returns a pointer to the associated `Texture2D` object.
     *
     * @return A pointer to the `Texture2D` object, or nullptr if no texture is associated with the mesh.
     */
    auto GetTexture() -> Texture2D* { return texture_.get(); }

    /**
     * @brief Creates a shared pointer to a Mesh object with the specified geometry.
     *
     * @param geometry A shared pointer to the Geometry object to be associated with the mesh.
     * @param texture A shared pointer to an optional Texture2D object to be associated with the mesh.
     * @return std::shared_ptr<Mesh> A shared pointer to the newly created Mesh object.
     */
    [[nodiscard]]
    static auto Create(
        std::shared_ptr<Geometry> geometry,
        std::shared_ptr<Texture2D> texture = nullptr
    ) {
        return std::make_shared<Mesh>(geometry, texture);
    }

private:
    /// @brief The geometry associated with the mesh.
    std::shared_ptr<Geometry> geometry_;
    /// @brief The texture associated with the mesh.
    std::shared_ptr<Texture2D> texture_;
};

}