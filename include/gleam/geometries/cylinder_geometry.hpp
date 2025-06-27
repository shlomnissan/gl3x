/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/geometries/geometry.hpp"

#include <memory>

namespace gleam {

/**
 * @brief A class for generating cylinder geometries.
 * @ingroup GeometryGroup
 */
class GLEAM_EXPORT CylinderGeometry : public Geometry {
public:
    /**
     * @brief Structure containing parameters for the cylinder geometry.
     */
    struct Parameters {
        float radius_top {1.0f};            ///< Radius of the cylinder.
        float radius_bottom {1.0f};         ///< Height of the cylinder.
        float height {1.0f};                ///< Height of the cylinder.
        unsigned int radial_segments {32};  ///< Number of segments along the radius.
        unsigned int height_segments {1};   ///< Number of segments along the height.
        bool open_ended {false};            ///< Whether the cylinder is open ended.
    };

    /**
     * @brief Constructs a CylinderGeometry object with the given parameters.
     *
     * @param params Parameters defining the size and segmentation of the cylinder.
     */
    explicit CylinderGeometry(const Parameters& params);

    /**
     * @brief Creates a shared pointer to a CylinderGeometry object with default parameters.
     *
     * @return std::shared_ptr<CylinderGeometry> A shared pointer to the newly created object.
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<CylinderGeometry>(Parameters {});
    }

    /**
     * @brief Creates a shared pointer to a CylinderGeometry object with the given parameters.
     *
     * @param params Parameters defining the size and segmentation of the plane.
     * @return std::shared_ptr<CylinderGeometry> A shared pointer to the newly created object.
     */
    [[nodiscard]] static auto Create(const Parameters& params){
        return std::make_shared<CylinderGeometry>(params);
    }

private:
    /**
     * @brief Generates the torso of the cylinder geometry.
     *
     * @param params Parameters defining the size and segmentation of the cylinder.
     */
    auto GenerateTorso(const Parameters& params) -> void;

    /**
     * @brief Generates the cap of the cylinder geometry.
     *
     * @param params Parameters defining the size and segmentation of the cylinder.
     * @param top Whether the cap is at the top or bottom of the cylinder.
     */
    auto GenerateCap(const Parameters& params, bool top) -> void;

    /**
     * @brief Sets the attributes for the cylinder geometry.
     */
    auto SetAttributes() -> void;
};

}