/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"
#include "gleam/math/utilities.hpp"

#include "gleam/nodes/camera.hpp"

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
 * class Application : public gleam::ApplicationContext {
 * public:
 *   auto Configure() -> void override {}
 *
 *   auto Setup() -> void override {
 *     SetCamera(gleam::PerspectiveCamera::Create({
 *       .fov = gleam::math::DegToRad(60.0f),
 *       .aspect = Context()->Parameters().ratio,
 *       .near = 0.1f,
 *       .far = 100.0f
 *     }));
 *   }
 *
 *   auto Update(float delta) -> bool override {
 *     return true;
 *   }
 * }
 * @endcode
 *
 * @ingroup NodesGroup
 */
class GLEAM_EXPORT PerspectiveCamera : public Camera {
public:
    /// @brief Parameters for constructing an PerspectiveCamera object.
    struct Parameters {
        float fov; ///< Camera frustum vertical field of view in radians.
        float aspect; ///< Camera frustum aspect ratio.
        float near; ///< Camera frustum near plane.
        float far; ///< Camera frustum far plane.
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
     * @brief Returns camera type.
     *
     * @return CameraType::PerspectiveCamera
     */
    [[nodiscard]] auto GetType() const -> CameraType override {
        return CameraType::PerspectiveCamera;
    }
};

}