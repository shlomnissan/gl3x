// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/core/geometry.hpp"

#include <memory>

namespace engine {

/**
 * @brief Class representing a plane geometry.
 */
class ENGINE_EXPORT PlaneGeometry : public Geometry {
public:
    /**
     * @brief Structure containing parameters for the plane geometry.
     */
    struct Parameters {
        float width {1};                ///< Width of the plane.
        float height {1};               ///< Height of the plane.
        unsigned width_segments {1};    ///< Number of segments along the width.
        unsigned height_segments {1};   ///< Number of segments along the height.
    };

    /**
     * @brief Constructs a PlaneGeometry object with the given parameters.
     *
     * @param params Parameters defining the size and segmentation of the plane.
     */
    explicit PlaneGeometry(const Parameters& params);

    /**
     * @brief Creates a shared pointer to a PlaneGeometry object with the specified parameters.
     *
     * @param params Parameters defining the size and segmentation of the plane.
     * @return std::shared_ptr<PlaneGeometry> A shared pointer to the newly created object.
     */
    [[nodiscard]] static auto Create(const Parameters& params){
        return std::make_shared<PlaneGeometry>(params);
    }

private:
    /**
     * @brief Generates the vertex and index data for the plane geometry.
     *
     * @param params Parameters defining the size and segmentation of the plane.
     */
    auto GenerateGeometry(const Parameters& params) -> void;

    /**
     * @brief Sets the attributes for the plane geometry.
     */
    auto SetAttributes() -> void;
};

}