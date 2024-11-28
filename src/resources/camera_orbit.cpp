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

    if (curr_scroll_offset_ != 0.0f) {
        Zoom(curr_scroll_offset_, delta);
        curr_scroll_offset_ = 0.0f;
    }

    prev_mouse_pos_ = curr_mouse_pos_;

    const auto position = Vector3 {
        distance * std::sin(orientation_.yaw) * std::cos(orientation_.pitch),
        distance * std::sin(orientation_.pitch),
        distance * std::cos(orientation_.yaw) * std::cos(orientation_.pitch)
    };

    auto f = Normalize(position - target);
    auto r = Normalize(Cross(Vector3::Up(), f));
    auto u = Cross(f, r);

    // the camera's transform will be inversed when the camera is updated
    // so there's no need to invert the 'look at' matrix here.
    camera_->transform = Transform {{
        {r.x, r.y, r.z, 0.0f},
        {u.x, u.y, u.z, 0.0f},
        {f.x, f.y, f.z, 0.0f},
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
    // TODO: implement panning
}

}