// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"
#include "gleam/core/events.hpp"
#include "gleam/math/vector2.hpp"
#include "gleam/math/vector3.hpp"
#include "gleam/nodes/node.hpp"
#include "gleam/nodes/camera_perspective.hpp"

#include <memory>

namespace engine {

/**
 * @brief Camera orbit node that allows the user to orbit, zoom and pan around a target point.
 */
class GLEAM_EXPORT OrbitControls : public Node {
public:
    /// @brief The speed at which the camera orbits around the target point.
    float orbit_speed {3.5f};

    /// @brief The speed at which the camera zooms in and out.
    float zoom_speed {50.0f};

    /// @brief The speed at which the camera pans around the target point.
    float pan_speed {1.5f};

    /**
     * @brief Parameters for configuring the camera orbit.
     */
    struct Parameters {
        float radius {1.0f}; ///< Distance of the camera from the target point.
        float pitch {0.0f}; ///< Pitch angle in radians, measured from the vertical axis.
        float yaw {0.0f}; ///< Yaw angle in radians, measured from the horizontal axis.
    };

    /**
     * @brief Constructs a CameraOrbit object.
     *
     * @param camera Shared pointer to the camera to orbit around.
     * @param params Parameters struct of the camera orbit.
     */
    OrbitControls(const std::shared_ptr<Camera>& camera, const Parameters& params)
        : camera_(camera), radius_(params.radius), pitch_(params.pitch), yaw_(params.yaw) {};

    /**
     * @brief Creates a new instance of the CameraOrbit class.
     *
     * @param camera Shared pointer to the camera to orbit around.
     * @param params Parameters struct of the camera orbit.
     * @return Shared pointer to the newly created instance.
     */
    [[nodiscard]] static auto Create(
        const std::shared_ptr<Camera>& camera,
        const Parameters& params
    ) {
        return std::make_shared<OrbitControls>(camera, params);
    }

    /**
     * @brief Invoked when a mouse event is received.
     *
     * @param event A pointer to the mouse event.
     */
    auto OnMouseEvent(MouseEvent* event) -> void override;

    /**
     * @brief Invoked when the node is updated.
     *
     * @param delta The time in seconds since the last update.
     */
    auto OnUpdate(float delta) -> void override;

private:
    /// @brief The camera to orbit around.
    std::shared_ptr<Camera> camera_;

    /// @brief The target point around which the camera orbits.
    Vector3 target = Vector3::Zero();

    /// @brief The current mouse position.
    Vector2 curr_mouse_pos_ {0.0f, 0.0f};

    /// @brief The previous mouse position.
    Vector2 prev_mouse_pos_ {0.0f, 0.0f};

    /// @brief The radius of the camera's orbit around the target.
    float radius_;

    /// @brief The pitch angle in radians, measured from the vertical axis.
    float pitch_;

    /// @brief The yawal angle in radians, measured from the horizontal axis.
    float yaw_;

    /// @brief The current vertical scroll offset.
    float curr_scroll_offset_ {0.0f};

    /// @brief Flag indicating whether the camera has been updated before.
    bool first_update_ {true};

    /**
     * @brief Orbits the camera around the target point.
     *
     * @param mouse_offset The offset of the mouse position.
     * @param delta The time in seconds since the last update.
     */
    auto Orbit(const Vector2& mouse_offset, float delta) -> void;

    /**
     * @brief Zooms the camera in and out.
     *
     * @param scroll_offset The vertical offset of the scroll wheel.
     * @param delta The time in seconds since the last update.
     */
    auto Zoom(float scroll_offset, float delta) -> void;

    /**
     * @brief Pans the camera around the target point.
     *
     * @param mouse_offset The offset of the mouse position.
     * @param delta The time in seconds since the last update.
     */
    auto Pan(const Vector2& mouse_offset, float delta) -> void;
};

}