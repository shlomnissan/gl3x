// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/core/events.hpp"
#include "engine/math/vector2.hpp"
#include "engine/math/vector3.hpp"
#include "engine/nodes/node.hpp"
#include "engine/nodes/camera_perspective.hpp"

#include <memory>

namespace engine {

/**
 * @brief A camera orbit node that allows the user to orbit around a target point.
 */
class ENGINE_EXPORT CameraOrbit : public Node {
public:
    /// @brief The speed at which the camera orbits around the target point.
    float orbit_speed {3.5f};

    /// @brief The speed at which the camera zooms in and out.
    float zoom_speed {50.0f};

    /// @brief The speed at which the camera pans around the target point.
    float pan_speed {1.5f};

    /**
     * @brief Constructs a CameraOrbit object.
     *
     * @param camera A shared pointer to the camera to orbit around.
     * @param radius The initial radius of the camera's orbit around the target.
     * @param polar The initial polar angle in radians.
     * @param azimuth The initial azimuthal angle in radians.
     */
    CameraOrbit(const std::shared_ptr<Camera>& camera, float radius, float polar, float azimuth);

    /**
     * @brief Creates a new instance of the CameraOrbit class.
     *
     * @param camera A shared pointer to the camera to orbit around.
     * @param radius The initial radius of the camera's orbit around the target.
     * @param polar The initial polar angle in radians.
     * @param azimuth The initial azimuthal angle in radians.
     * @return A `std::shared_ptr<CameraOrbit>` pointing to the newly created instance.
     */
    [[nodiscard]] static auto Create(
        const std::shared_ptr<Camera>& camera,
        float radius,
        float polar = 0.0f,
        float azimuth = 0.0f
    ) {
        return std::make_shared<CameraOrbit>(camera, radius, polar, azimuth);
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
    auto Update(float delta) -> void override;

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

    /// @brief The polar angle in radians, measured from the vertical axis.
    float polar_;

    /// @brief The azimuthal angle in radians, measured from the horizontal axis.
    float azimuth_;

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