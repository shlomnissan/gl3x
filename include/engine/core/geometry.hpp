// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <vector>

namespace engine {

/**
 * @brief Enum representing the type of a geometry attribute.
 */
enum class ENGINE_EXPORT GeometryAttributeType {
    kPosition,  ///< Position attribute.
    kNormal,    ///< Normal attribute.
    kUV,        ///< UV attribute.
};

/**
 * @brief Structure representing a geometry attribute.
 */
struct ENGINE_EXPORT GeometryAttribute {
    /// @brief The type of the attribute.
    GeometryAttributeType type;
    /// @brief The number of components per vertex.
    unsigned int item_size;
    /// @brief The offset of the attribute in the vertex data.
    unsigned int offset;
};

/**
 * @brief Class representing a 3D geometry with vertex and index data.
 */
class ENGINE_EXPORT Geometry {
public:
    /**
     * @brief Default construction. 
     */
    Geometry() = default;

    /**
     * @brief Constructs a Geometry object with given vertex and index data.
     *
     * @param vertex_data A vector containing the vertex data.
     * @param index_data A vector containing the index data (optional).
     */
    Geometry(
        const std::vector<float>& vertex_data,
        const std::vector<unsigned int>& index_data = {}
    ) : vertex_data_(vertex_data), index_data_(index_data) {}

    /**
     * @brief Gets the vertex data of the geometry.
     *
     * @return const std::vector<float>& A reference to the vector containing the vertex data.
     */
    [[nodiscard]]
    const auto& VertexData() const { return vertex_data_; }

    /**
     * @brief Gets the index data of the geometry.
     *
     * @return const std::vector<unsigned int>& A reference to the vector containing the index data.
     */
    [[nodiscard]]
    const auto& IndexData() const { return index_data_; }

    /**
     * @brief Gets the attributes of the geometry.
     *
     * @return const std::vector<GeometryAttribute>& A reference to the vector containing the geometry attributes.
     */
    [[nodiscard]]
    const auto& Attributes() const { return attributes_; }

    /**
     * @brief Sets a geometry attribute.
     *
     * @param attribute The attribute to set.
     */
    auto SetAttribute(const GeometryAttribute& attribute) -> void;

protected:
    /// @brief The vertex data of the geometry.
    std::vector<float> vertex_data_;
    /// @brief The index data of the geometry.
    std::vector<unsigned int> index_data_;
    /// @brief The attributes of the geometry.
    std::vector<GeometryAttribute> attributes_;
};

}