/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/cameras/camera.hpp"
#include "gleam/nodes/node.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Interactive camera controller for orbiting around a target point.
 *
 * `OrbitControls` enables intuitive camera manipulation using spherical coordinates,
 * allowing users to orbit, zoom, and pan around a fixed target. It is typically
 * attached to a scene node and linked to a `Camera` instance, responding to mouse
 * input and updating camera transforms each frame.
 *
 * This controller is useful for editor views, previews, and navigation interfaces.
 *
 * @code
 * auto MyScene::OnAttached(const gleam::SharedContext* context) -> void override {
 *   Add(gleam::OrbitControls::Create(
 *     context->Parameters().camera, {
 *       .radius = 5.0f,
 *       .pitch = math::DegToRad(25.0f),
*        .yaw = math::DegToRad(45.0f)
 *     }
 *   ));
 * }
 * @endcode
 *
 * @ingroup NodesGroup
 */
class GLEAM_EXPORT OrbitControls : public Node {
public:
    float orbit_speed {3.5f}; ///< Rate at which the camera orbits around the target point.
    float zoom_speed {50.0f}; ///< Rate at which the camera zooms in and out.
    float pan_speed {0.5f}; ///< Rate at which the camera pans around the target point.

    /**
     * @brief Parameters for constructing a CameraOrbit object.
     */
    struct Parameters {
        float radius {1.0f}; ///< Distance of the camera from the target point.
        float pitch {0.0f}; ///< Pitch angle in radians, measured from the vertical axis.
        float yaw {0.0f}; ///< Yaw angle in radians, measured from the horizontal axis.
    };

    /**
     * @brief Constructs a CameraOrbit object.
     *
     * @param camera Pointer to the camera to orbit around.
     * @param params OrbitControls::Parameters
     */
    OrbitControls(Camera* camera, const Parameters& params);

    /**
     * @brief Creates a shared pointer to a OrbitCamera object.
     *
     * @param camera Pointer to the camera to orbit around.
     * @param params OrbitControls::Parameters
     * @return std::shared_ptr<OrbitControls>
     */
    [[nodiscard]] static auto Create(Camera* camera, const Parameters& params) {
        return std::make_shared<OrbitControls>(camera, params);
    }

    /**
     * @brief Mouse event handler.
     *
     * @param event Pointer to the mouse event.
     */
    auto OnMouseEvent(MouseEvent* event) -> void override;

    /**
     * @brief Updates the camera control each frame.
     *
     * @param delta Time in seconds since the last update.
     */
    auto OnUpdate(float delta) -> void override;

    /**
     * @brief Destructor.
     */
    ~OrbitControls();

private:
    /// @cond INTERNAL
    class Impl;
    std::unique_ptr<Impl> impl_;
    /// @endcond
};

}