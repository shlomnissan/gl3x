/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/cameras/camera.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Represents a camera that uses perspective projection.
 *
 * This projection mode is designed to mimic the way the human eye sees. It is
 * the most common projection mode used for rendering a 3D scene.
 *
 * Although multiple cameras can be added to the scene graph and inherit
 * transformations from their parent objects, only one camera can be active at
 * a time. The active camera is managed by the application’s runtime object:
 * @code
 * class MyApp : public gleam::Application {
 * public:
 *   auto Configure() -> void override {}
 *
 *   auto Setup() -> void override {
 *     SetCamera(gleam::PerspectiveCamera::Create({
 *       .fov = gleam::math::DegToRad(60.0f),
 *       .aspect = Context()->Parameters().ratio,
 *       .near = 0.1f,
 *       .far = 1000.0f
 *     }));
 *   }
 *
 *   auto Update(float delta) -> bool override {
 *     return true;
 *   }
 * }
 * @endcode
 *
 * @ingroup CamerasGroup
 */
class GLEAM_EXPORT PerspectiveCamera : public Camera {
public:
    /// @brief Parameters for constructing an PerspectiveCamera object.
    struct Parameters {
        float fov; ///< Vertical field of view in radians.
        float aspect; ///< Aspect ratio.
        float near; ///< Distance to the near clipping plane
        float far; ///< Distance to the far clipping plane
    };

    /**
     * @brief Constructs an PerspectiveCamera object.
     *
     * @param params PerspectiveCamera::Parameters
     */
    explicit PerspectiveCamera(const Parameters& params);

    /**
     * @brief Creates a shared pointer to an PerspectiveCamera object.
     *
     * @param params PerspectiveCamera::Parameters
     * @return std::shared_ptr<PerspectiveCamera>
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<PerspectiveCamera>(params);
    }

    /**
     * @brief Updates the projection transform to match the new viewport size.
     *
     * @param width Viewport width in pixels.
     * @param height Viewport height in pixels.
     */
    auto Resize(int width, int height) -> void override;

    /**
     * @brief Configures perspective projection parameters.
     *
     * Updates the camera's vertical field of view, near plane, and far plane,
     * and rebuilds the projection transform accordingly. The aspect ratio
     * remains unchanged until @ref Resize is called.
     *
     * @param fov  Vertical field of view in radians.
     * @param near Distance to the near clipping plane.
     * @param far  Distance to the far clipping plane.
     */
    auto SetLens(float fov, float near, float far) -> void;

private:
    /// @cond INTERNAL
    Parameters params_;
    /// @endcond
};

}