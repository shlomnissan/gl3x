/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"
#include "gleam/core/geometry.hpp"
#include "gleam/math/vector3.hpp"

#include <memory>

namespace gleam {

/**
 * @brief A class for generating box geometries.
 * @ingroup GeometryGroup
 */
class GLEAM_EXPORT BoxGeometry : public Geometry {
public:
    /**
     * @brief Structure containing parameters for the box geometry.
     */
    struct Parameters {
        float width {1.0f};             ///< Width of the box.
        float height {1.0f};            ///< Height of the box.
        float depth {1.0f};             ///< Depth of the box.
        unsigned width_segments {1};    ///< Number of segments along the width.
        unsigned height_segments {1};   ///< Number of segments along the height.
        unsigned depth_segments {1};    ///< Number of segments along the depth.
    };

    /**
     * @brief Constructs a BoxGeometry object with the given parameters.
     *
     * @param params Parameters defining the size and segmentation of the box.
     */
    explicit BoxGeometry(const Parameters& params);

    /**
     * @brief Creates a shared pointer to a BoxGeometry object with default parameters.
     *
     * @return std::shared_ptr<BoxGeometry> A shared pointer to the newly created object.
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<BoxGeometry>(Parameters {});
    }

    /**
     * @brief Creates a shared pointer to a BoxGeometry object with the given parameters.
     *
     * @param params Parameters defining the size and segmentation of the box.
     * @return std::shared_ptr<BoxGeometry> A shared pointer to the newly created object.
     */
    [[nodiscard]] static auto Create(const Parameters& params){
        return std::make_shared<BoxGeometry>(params);
    }

private:
    /// @brief Vertices counter.
    unsigned vertex_counter_ {0};

    /**
     * @brief Structure containing parameters for the BuildPlane method.
     */
    struct PlaneParameters {
        char u;             ///< 1st axis ('x', 'y', or 'z').
        char v;             ///< 2nd axis ('x', 'y', or 'z').
        char w;             ///< 3rd axis ('x', 'y', or 'z').
        int udir;           ///< Horizontal direction.
        int vdir;           ///< Vertical direction.
        float width;        ///< Width of the plane.
        float height;       ///< Height of the plane.
        float depth;        ///< Depth of the plane.
        unsigned grid_x;    ///< Horizontal segments.
        unsigned grid_y;    ///< Vertical segments.
    };

    /**
     * @brief Sets the value of a specific component in the vector.
     *
     * @param vec Reference to the vector whose component will be modified.
     * @param axis Character representing the axis ('x', 'y', or 'z') to update.
     * @param value The new value to assign to the specified component.
     */
    auto SetComponent(Vector3& vec, char axis, float value) -> void;

    /**
     * @brief Generates an individual plane for the box geometry.
     *
     * @param params Parameters defining the size, direction, and segmentation of a plane.
     */
    auto BuildPlane(const PlaneParameters& params) -> void;

    /**
     * @brief Sets the attributes for the box geometry.
     */
    auto SetAttributes() -> void;
};

}