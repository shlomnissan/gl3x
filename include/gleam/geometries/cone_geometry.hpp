// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"
#include "gleam/core/geometry.hpp"
#include "gleam/geometries/cylinder_geometry.hpp"

#include <memory>

namespace engine {

/**
 * @brief A class for generating cone geometries.
 * @ingroup GeometryGroup
 */
class GLEAM_EXPORT ConeGeometry : public CylinderGeometry {
public:
    /**
     * @brief Structure containing parameters for the cone geometry.
     */
    struct Parameters {
        float radius {1.0f};            ///< Radius of the cone.
        float height {1.0f};            ///< Height of the cone.
        unsigned radial_segments {16};  ///< Number of segments along the radius.
        unsigned height_segments {1};   ///< Number of segments along the height.
        bool open_ended {false};        ///< Whether the cone is open ended.
    };

    /**
     * @brief Constructs a ConeGeometry object with the given parameters.
     *
     * @param params Parameters defining the size and segmentation of the cone.
     */
    explicit ConeGeometry(const Parameters& params);

    /**
     * @brief Creates a shared pointer to a ConeGeometry object with default parameters.
     *
     * @return std::shared_ptr<ConeGeometry> A shared pointer to the newly created object.
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<ConeGeometry>(Parameters {});
    }

    /**
     * @brief Creates a shared pointer to a ConeGeometry object with the given parameters.
     *
     * @param params Parameters defining the size and segmentation of the cone.
     * @return std::shared_ptr<ConeGeometry> A shared pointer to the newly created object.
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<ConeGeometry>(params);
    }
};

}