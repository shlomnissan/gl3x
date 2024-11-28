// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/resources/camera_orbit.hpp"

#include "engine/math/vector3.hpp"

#include <algorithm>
#include <cmath>

namespace engine {

auto CameraOrbit::OnMouseEvent(MouseEvent* event) -> void {
    using enum MouseButton;
    using enum MouseEvent::Type;

    curr_mouse_pos_ = event->position;

    if (event->type == ButtonPressed && curr_mouse_button_ == None) {
        curr_mouse_button_ = event->button;
    }

    if (event->type == ButtonReleased && event->button == curr_mouse_button_) {
        curr_mouse_button_ = None;
    }

    if (event->type == Scrolled) {
        curr_scroll_offset_ = event->scroll.y;
    }
}

auto CameraOrbit::Update(float delta) -> void {
    if (!first_update_) {
        first_update_ = true;
        prev_mouse_pos_ = curr_mouse_pos_;
        return;
    }

    auto mouse_offset = curr_mouse_pos_ - prev_mouse_pos_;

    if (curr_mouse_button_ == MouseButton::Left) {
        Orbit(mouse_offset, delta);
    }

    if (curr_mouse_button_ == MouseButton::Right) {
        Pan(mouse_offset, delta);
    }

    if (curr_scroll_offset_ != 0.0f) {
        Zoom(curr_scroll_offset_, delta);
        curr_scroll_offset_ = 0.0f;
    }

    prev_mouse_pos_ = curr_mouse_pos_;

    const auto position = target + Vector3 {
        distance * std::sin(orientation_.yaw) * std::cos(orientation_.pitch),
        distance * std::sin(orientation_.pitch),
        distance * std::cos(orientation_.yaw) * std::cos(orientation_.pitch)
    };

    const auto forward = Normalize(position - target);
    const auto right = Normalize(Cross(Vector3::Up(), forward));
    const auto up = Cross(forward, right);

    // the camera's transform will be inversed when the camera is updated
    // so there's no need to invert the 'look at' matrix here.
    camera_->transform = Transform {{
        {right.x, right.y, right.z, 0.0f},
        {up.x, up.y, up.z, 0.0f},
        {forward.x, forward.y, forward.z, 0.0f},
        {position.x, position.y, position.z, 1.0f}
    }};
}

auto CameraOrbit::Orbit(const Vector2& offset, float delta) -> void {
    orientation_.yaw -= offset.x * orbit_speed * delta;
    orientation_.pitch += offset.y * orbit_speed * delta;
    orientation_.pitch = std::clamp(orientation_.pitch, -pitch_limit, pitch_limit);
}

auto CameraOrbit::Zoom(float scroll_offset, float delta) -> void {
    distance -= scroll_offset * zoom_speed * delta;
    distance = std::max(0.1f, distance);
}

auto CameraOrbit::Pan(const Vector2& offset, float delta) -> void {
    const auto forward = Normalize(target - camera_->transform.GetPosition());
    const auto right = Normalize(Cross(forward, Vector3::Up()));
    const auto up = Cross(right, forward);

    const auto pan_h = right * offset.x * pan_speed * delta;
    const auto pan_v = up * -offset.y * pan_speed * delta;

    target = target - (pan_h + pan_v);
}

}