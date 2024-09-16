// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/core/geometry.hpp"
#include "engine/math/vector3.hpp"

#include <memory>

namespace engine {

/**
 * @brief Class representing a box geometry.
 */
class ENGINE_EXPORT BoxGeometry : public Geometry {
public:
    /**
     * @brief Structure containing parameters for the box geometry.
     */
    struct Parameters {
        float width = 1;                ///< Width of the box.
        float height = 1;               ///< Height of the box.
        float depth = 1;                ///< Depth of the box.
        unsigned width_segments = 1;    ///< Number of segments along the width.
        unsigned height_segments = 1;   ///< Number of segments along the height.
        unsigned depth_segments = 1;    ///< Number of segments along the depth.
    };

    /**
     * @brief Constructs a BoxGeometry object with the given parameters.
     *
     * @param params Parameters defining the size and segmentation of the box.
     */
    explicit BoxGeometry(const Parameters& params);

    /**
     * @brief Creates a shared pointer to a BoxGeometry object with the specified parameters.
     *
     * @param params Parameters defining the size and segmentation of the box.
     * @return std::shared_ptr<BoxGeometry> A shared pointer to the newly created object.
     */
    [[nodiscard]]
    static auto Create(const Parameters& params){
        return std::make_shared<BoxGeometry>(params);
    }

private:
    /// @brief Vertices counter.
    unsigned vertex_counter_ {0};

    /**
     * @brief Structure containing parameters for the BuildPlane method.
     */
    struct PlaneParams {
        char u;             ///< 1st dimension (x, y, or z).
        char v;             ///< 2nd dimension (x, y, or z).
        char w;             ///< 3rd dimension (x, y, or z).
        int udir;           ///< Horizontal direction.
        int vdir;           ///< Vertical direction.
        float width;        ///< Width of the plane.
        float height;       ///< Height of the plane.
        float depth;        ///< Depth of the plane.
        unsigned grid_x;    ///< Horizontal segments.
        unsigned grid_y;    ///< Vertical segments.
    };

    /**
     * @brief Generates an individual plane for the box geometry.
     *
     * @param params Parameters defining the size, direction, and segmentation of a plane.
     */
    auto BuildPlane(const PlaneParams& params) -> void;

    /**
     * @brief Sets the attributes for the box geometry.
     */
    auto SetAttributes() -> void;
};

}