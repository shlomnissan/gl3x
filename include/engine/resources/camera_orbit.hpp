// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/euler.hpp"
#include "engine/math/vector2.hpp"
#include "engine/math/vector3.hpp"
#include "engine/math/utilities.hpp"
#include "engine/scene/node.hpp"
#include "engine/scene/camera_perspective.hpp"

#include "core/event.hpp"

#include <memory>

namespace engine {

/**
 * @brief A camera orbit node that allows the user to orbit around a target point.
 */
class ENGINE_EXPORT CameraOrbit : public Node {
public:
    /// @brief The maximum pitch angle limit to prevent the camera from flipping over.
    static constexpr float pitch_limit = math::half_pi - 0.1f;

    /// @brief The speed at which the camera orbits around the target point.
    float orbit_speed = 3.5f;

    /// @brief The speed at which the camera zooms in and out.
    float zoom_speed = 50.0f;

    /// @brief The speed at which the camera pans around the target point.
    float pan_speed = 2.0f;

    /// @brief The distance from the camera to the target point.
    float distance = 1.0f;

    /**
     * @brief Constructs a CameraOrbit object.
     *
     * @param camera A shared pointer to the camera to orbit around.
     */
    explicit CameraOrbit(const std::shared_ptr<Camera>& camera) : camera_(camera) {}

    /**
     * @brief Creates a new instance of the CameraOrbit class.
     *
     * @param camera A shared pointer to the camera to orbit around.
     * @return A `std::shared_ptr<CameraOrbit>` pointing to the newly created instance.
     */
    [[nodiscard]] static auto Create(const std::shared_ptr<Camera>& camera) {
        return std::make_shared<CameraOrbit>(camera);
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
    /// @brief The current orientation of the camera in Euler angles.
    Euler orientation_ {};

    /// @brief The current mouse button.
    MouseButton curr_mouse_button_ {MouseButton::None};

    /// @brief The camera to orbit around.
    std::shared_ptr<Camera> camera_;

    /// @brief The target point around which the camera orbits.
    Vector3 target = Vector3::Zero();

    /// @brief The current mouse position.
    Vector2 curr_mouse_pos_ {0.0f, 0.0f};

    /// @brief The previous mouse position.
    Vector2 prev_mouse_pos_ {0.0f, 0.0f};

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