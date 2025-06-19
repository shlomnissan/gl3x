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
 * @brief Represents a camera that uses orthographic projection.
 *
 * In this projection mode, an object's size in the rendered image stays
 * constant regardless of its distance from the camera. This can be useful for
 * rendering 2D scenes and UI elements, amongst other things.
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
 *     SetCamera(gleam::OrthographicCamera::Create({
 *       .left = 0.0f,
 *       .right = 1024.0f,
 *       .top = 0.0f,
 *       .bottom = 768.0f,
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
 * @ingroup CamerasGroup
 */
class GLEAM_EXPORT OrthographicCamera : public Camera {
public:
    /// @brief Parameters for constructing an OrthographicCamera object.
    struct Parameters {
        float left; ///< Camera frustum left plane.
        float right; ///< Camera frustum right plane.
        float top; ///< Camera frustum top plane.
        float bottom; ///< Camera frustum bottom plane.
        float near; ///< Camera frustum near plane.
        float far; ///< Camera frustum far plane.
    };

   /**
     * @brief Constructs an OrthographicCamera object.
     *
     * @param params OrthographicCamera::Parameters
     */
    explicit OrthographicCamera(const Parameters& params);

    /**
     * @brief Creates a shared pointer to an OrthographicCamera object.
     *
     * @param params OrthographicCamera::Parameters
     * @return std::shared_ptr<OrthographicCamera>
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<OrthographicCamera>(params);
    }

    /**
     * @brief Returns camera type.
     *
     * @return CameraType::OrthographicCamera
     */
    [[nodiscard]] auto GetType() const -> CameraType override {
        return CameraType::OrthographicCamera;
    }
};

}