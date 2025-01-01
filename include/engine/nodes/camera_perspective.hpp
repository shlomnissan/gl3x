// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/math/utilities.hpp"

#include "engine/nodes/camera.hpp"

#include <memory>

namespace engine {

/**
 * @brief A perspective camera class.
 *
 * This class represents a perspective camera in the scene. It extends the Camera class
 * and provides functionality specific to a perspective projection.
 */
class ENGINE_EXPORT CameraPerspective : public Camera {
public:
    /**
     * @brief The parameters of the perspective camera.
     */
    struct Parameters {
        float fov = 60.0f;      ///< The field of view in degrees.
        float aspect = 1.77f;   ///< The aspect ratio of the camera.
        float near = 0.1f;      ///< The distance to the near clipping plane.
        float far = 1000.0f;    ///< The distance to the far clipping plane.
    };

    /**
    * @brief Constructs a CameraPerspective object.
    *
    * @param params The parameters struct of the perspective camera.
    */
    explicit CameraPerspective(const Parameters& params);

    /**
     * @brief Creates a new instance of the CameraPerspective class with default parameters.
     *
     * @return A `std::shared_ptr<CameraPerspective>` pointing to the newly created instance.
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<CameraPerspective>(Parameters {});
    }

    /**
     * @brief Creates a new instance of the CameraPerspective class.
     *
     * @param params The parameters struct of the perspective camera.
     * @return A `std::shared_ptr<CameraPerspective>` pointing to the newly created instance.
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<CameraPerspective>(params);
    }

private:
    /// @brief The parameters of the perspective camera.
    Parameters params_;

    /**
     * @brief Sets the perspective projection matrix.
     */
    auto SetProjection() -> void override;
};

}