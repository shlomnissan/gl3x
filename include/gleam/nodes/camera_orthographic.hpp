// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"

#include "gleam/nodes/camera.hpp"

#include <memory>

namespace gleam {

/**
 * @brief An orthographic camera class.
 *
 * This class represents an orthographic camera in the scene. It extends the Camera class
 * and provides functionality specific to an orthographic projection.
 */
class GLEAM_EXPORT CameraOrthographic : public Camera {
public:
    /**
     * @brief The parameters of the orthographic camera.
     */
    struct Parameters {
        float left = -1.0f;     ///< The left bound of the view volume.
        float right = 1.0f;     ///< The right bound of the view volume.
        float top = 1.0f;       ///< The top bound of the view volume.
        float bottom = -1.0f;   ///< The bottom bound of the view volume.
        float near = 0.1f;      ///< The distance to the near clipping plane.
        float far = 100.0f;     ///< The distance to the far clipping plane;
    };

    /**
     * @brief Constructs an orthographic camera object.
     *
     * @param params The parameters struct of the orthographic camera.
     */
    explicit CameraOrthographic(const Parameters& params);

    /**
     * @brief Creates a new instance of the CameraOrthographic class with default parameters.
     *
     * @return A `std::shared_ptr<CameraOrthographic>` pointing to the newly created instance.
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<CameraOrthographic>(Parameters {});
    }

    /**
     * @brief Creates a new instance of the CameraOrthographic class.
     *
     * @param params The parameters struct of the orthographic camera.
     * @return A `std::shared_ptr<CameraOrthographic>` pointing to the newly created instance.
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<CameraOrthographic>(params);
    }

private:
    /// @brief The parameters of the orthographic camera.
    Parameters params_;

    /**
     * @brief Sets the orthographic projection matrix.
     */
    auto SetProjection() -> void override;
};

}