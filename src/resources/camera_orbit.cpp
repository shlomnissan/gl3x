// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/resources/camera_orbit.hpp"

#include <algorithm>

namespace engine {

auto CameraOrbit::OnMouseEvent(MouseEvent* event) -> void {
    using enum MouseButton;
    using enum MouseEvent::Type;

    curr_mouse_pos_ = event->position;
    if (!first_update_) {
        first_update_ = true;
        prev_mouse_pos_ = curr_mouse_pos_;
    }


    if (event->type == ButtonPressed && curr_mouse_button_ == None) {
        curr_mouse_button_ = event->button;
    }

    if (event->type == ButtonReleased && event->button == curr_mouse_button_) {
        curr_mouse_button_ = None;
    }
}

auto CameraOrbit::Update(float delta) -> void {
    if (curr_mouse_button_ == MouseButton::Left) {
        auto mouse_offset = curr_mouse_pos_ - prev_mouse_pos_;

        if (curr_mouse_button_ == MouseButton::Left) {
            Orbit(mouse_offset, delta);
        }

        prev_mouse_pos_ = curr_mouse_pos_;
    }
}

auto CameraOrbit::Orbit(const Vector2& offset, float delta) -> void {
    orientation_.yaw -= offset.x * orbit_speed * delta;
    orientation_.pitch -= std::clamp(offset.y * orbit_speed * delta, -pitch_limit, pitch_limit);
}

}