/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"
#include "gleam/core/disposable.hpp"
#include "gleam/core/identity.hpp"
#include "gleam/math/box3.hpp"
#include "gleam/math/sphere.hpp"
#include "gleam/math/utilities.hpp"

#include <memory>
#include <optional>
#include <vector>

namespace gleam {

/**
 * @brief Represents available vertex attributes.
 * @ingroup GeometryGroup
 */
enum class GeometryAttributeType {
    Position, ///< Vertex position.
    Normal, ///< Vertex normal vector.
    UV, ///< Texture coordinates.
};

/**
 * @brief Represents primitive topologies for rendering geometry.
 * @ingroup GeometryGroup
 */
enum class GeometryPrimitiveType {
    Triangles, ///< Renders geometry as individual triangles.
    Lines, ///< Renders geometry as disconnected lines.
    LineLoop ///< Renders geometry as a connected loop of lines.
};

/**
 * @brief Represents a vertex attribute layout.
 * @ingroup GeometryGroup
 */
struct GeometryAttribute {
    /// @brief Semantic type of the attribute.
    GeometryAttributeType type;
    /// @brief Number of components (e.g., 3 for Vector3).
    unsigned int item_size;
};

/**
 * @brief Represents GPU-ready geometry data including vertex and index buffers.
 *
 * The `Geometry` class is the fundamental unit of renderable mesh data in Gleam.
 * It contains raw vertex data, optional indices, and layout metadata. Geometry
 * can be rendered using different primitive types (triangles, lines, etc.) and
 * may expose bounds such as bounding boxes and spheres for culling or physics.
 *
 * Instances are typically created using the static `Create()` methods and then
 * configured with attribute metadata via `SetAttribute`.
 *
 * @code
 * auto geometry = Geometry::Create({
 *    0.5f, -0.5f, 0.0f,
 *    0.0f,  0.5f, 0.0f,
 *   -0.5f, -0.5f, 0.0f,
 * });
 *
 * geometry->SetAttribute({GeometryAttributeType::Position, 3});
 * Add(Mesh::Create(geometry, FlatMaterial::Create(0xFF0133)));
 * @endcode
 *
 * @ingroup GeometryGroup
 */
class GLEAM_EXPORT Geometry : public Disposable, public Identity {
public:
    /// @brief Primitive type used for rendering.
    GeometryPrimitiveType primitive { GeometryPrimitiveType::Triangles };

    /// @brief GPU renderer identifier. Used internally by the renderer.
    unsigned int renderer_id = 0;

    /**
     * @brief  Constructs a Geometry object.
     */
    Geometry() = default;

    /**
     * @brief Constructs a Geometry object with vertex and index data.
     *
     * @param vertex_data Flat float array of interleaved vertex attributes.
     * @param index_data Optional index buffer for indexed rendering.
     */
    Geometry(
        const std::vector<float>& vertex_data,
        const std::vector<unsigned int>& index_data
    ) : vertex_data_(vertex_data), index_data_(index_data) {}

    /**
     * @brief Creates a shared pointer to a Geometry object.
     *
     * @return std::shared_ptr<Geometry>
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<Geometry>();
    }

    /**
     * @brief Creates a shared pointer to a Geometry object with vertex and index data.
     *
     * @param vertex_data Flat float array of interleaved vertex attributes.
     * @param index_data Optional index buffer for indexed rendering.
     * @return std::shared_ptr<Geometry>
     */
    [[nodiscard]] static auto Create(
        const std::vector<float>& vertex_data,
        const std::vector<unsigned int>& index_data = {}
    ){
        return std::make_shared<Geometry>(vertex_data, index_data);
    }

    /**
     * @brief Returns raw vertex data.
     *
     * @return Reference to the float vector containing vertex buffer data.
     */
    [[nodiscard]] const auto& VertexData() const { return vertex_data_; }

    /**
     * @brief Returns the number of vertices (size / stride).
     */
    [[nodiscard]] auto VertexCount() const -> size_t;

    /**
     * @brief Returns raw index data.
     *
     * @return Reference to the vector containing index buffer data.
     */
    [[nodiscard]] const auto& IndexData() const { return index_data_; }

    /**
     * @brief Returns the number of indices.
     */
    [[nodiscard]] auto IndexCount() const -> size_t { return index_data_.size(); }

    /**
     * @brief Returns all defined vertex attributes.
     *
     * @return Reference to the vector containing vertex attributes.
     */
    [[nodiscard]] const auto& Attributes() const { return attributes_; }

    /**
     * @brief Returns the vertex stride in floats (sum of all active attribute sizes).
     */
    [[nodiscard]] auto Stride() const -> size_t;

    /**
     * @brief Adds a vertex attribute.
     *
     * @param attribute The attribute to register.
     */
    auto SetAttribute(const GeometryAttribute& attribute) -> void;

    /**
     * @brief Returns whether a given attribute type is present.
     *
     * @param type Attribute type to query.
     */
    [[nodiscard]] auto HasAttribute(GeometryAttributeType type) const -> bool;

    /**
     * @brief Returns the geometry's bounding box (computed on demand).
     *
     * If not cached, it will be computed from the position data.
     */
    [[nodiscard]] auto BoundingBox() -> Box3;

    /**
     * @brief Returns the geometry's bounding sphere (computed on demand).
     *
     * If not cached, it will be computed from the position data.
     */
    [[nodiscard]] auto BoundingSphere() -> Sphere;

    /**
     * @brief Destructor.
     */
    virtual ~Geometry();

protected:
    /// @brief Interleaved vertex buffer.
    std::vector<float> vertex_data_;

    /// @brief Index buffer.
    std::vector<unsigned int> index_data_;

    /// @brief Cached bounding box.
    std::optional<Box3> bounding_box_;

    /// @brief Cached bounding sphere.
    std::optional<Sphere> bounding_sphere_;

    /// @brief Vertex attribute metadata.
    std::vector<GeometryAttribute> attributes_;

    /**
     * @brief Computes and caches the bounding box.
     */
    auto CreateBoundingBox() -> void;

    /**
     * @brief Computes and caches the bounding sphere.
     */
    auto CreateBoundingSphere() -> void;
};

}