// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/core/geometry.hpp"

#include <memory>

namespace engine {

/**
 * @brief Class representing a cylinder geometry.
 */
class ENGINE_EXPORT CylinderGeometry : public Geometry {
public:
    /**
     * @brief Structure containing parameters for the cylinder geometry.
     */
    struct Paramaters {
        float radius_top {1};               ///< Radius of the cylinder.
        float radius_bottom {1};            ///< Height of the cylinder.
        float height {1};                   ///< Height of the cylinder.
        unsigned int radial_segments {32};  ///< Number of segments along the radius.
        unsigned int height_segments {1};   ///< Number of segments along the height.
        bool open_ended {false};            ///< Whether the cylinder is open ended.
    };

    /**
     * @brief Constructs a CylinderGeometry object with the given parameters.
     *
     * @param params Parameters defining the size and segmentation of the cylinder.
     */
    explicit CylinderGeometry(const Paramaters& params);

    /**
     * @brief Creates a shared pointer to a CylinderGeometry object with the given parameters.
     *
     * @param params Parameters defining the size and segmentation of the plane.
     * @return std::shared_ptr<CylinderGeometry> A shared pointer to the newly created object.
     */
    [[nodiscard]] static auto Create(const Paramaters& params){
        return std::make_shared<CylinderGeometry>(params);
    }

private:
    /**
     * @brief Generates the torso of the cylinder geometry.
     */
    auto GenerateTorso() -> void;

    /**
     * @brief Generates the cap of the cylinder geometry.
     *
     * @param top Whether the cap is at the top or bottom of the cylinder.
     */
    auto GenerateCap(bool top) -> void;

    /**
     * @brief Sets the attributes for the cylinder geometry.
     */
    auto SetAttributes() -> void;
};

}