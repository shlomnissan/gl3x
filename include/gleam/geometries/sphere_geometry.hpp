/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/geometries/geometry.hpp"
#include "gleam/math/utilities.hpp"

#include <memory>

namespace gleam {

/**
 * @brief A class for generating sphere geometries.
 */
class GLEAM_EXPORT SphereGeometry : public Geometry {
public:
    /**
     * @brief Structure containing parameters for the sphere geometry.
     */
    struct Parameters {
        float radius {1.0f};                ///< Radius of the sphere.
        unsigned width_segments {32};       ///< Number of horizontal segments.
        unsigned height_segments {16};      ///< Number of vertical segments.
        float phi_start {0.0f};             ///< Horizontal starting angle.
        float phi_length {math::two_pi};    ///< Horizontal sweep angle size.
        float theta_start {0.0f};           ///< Vertical starting angle.
        float theta_length {math::pi};      ///< Vertical sweep angle size.
    };

    /**
     * @brief Constructs a SphereGeometry object with the given parameters.
     *
     * @param params Parameters defining the radius and segmentation of the sphere.
     */
    explicit SphereGeometry(const Parameters& params);

    /**
     * @brief Creates a shared pointer to a SphereGeometry object with default parameters.
     *
     * @return std::shared_ptr<SphereGeometry> A shared pointer to the newly created object.
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<SphereGeometry>(Parameters {});
    }

    /**
     * @brief Creates a shared pointer to a SphereGeometry object with the given parameters.
     *
     * @param params Parameters defining the radius and segmentation of the sphere.
     * @return std::shared_ptr<SphereGeometry> A shared pointer to the newly created object.
     */
    [[nodiscard]] static auto Create(const Parameters& params){
        return std::make_shared<SphereGeometry>(params);
    }

private:
    /**
     * @brief Generates the vertex and index data for the sphere geometry.
     *
     * @param params Parameters defining the radius and segmentation of the sphere.
     */
    auto GenerateGeometry(const Parameters& params) -> void;

    /**
     * @brief Sets the attributes for the sphere geometry.
     */
    auto SetAttributes() -> void;
};

}