/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/cameras/orbit_controls.hpp"

#include "gleam/math/utilities.hpp"

#include <algorithm>
#include <cmath>

namespace gleam {

constexpr auto kVerticalLimit = math::half_pi - 0.1f;

auto OrbitControls::OnMouseEvent(MouseEvent* event) -> void {
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

auto OrbitControls::OnUpdate(float delta) -> void {
    if (!first_update_) {
        first_update_ = true;
        prev_mouse_pos_ = curr_mouse_pos_;
        return;
    }

    const auto mouse_offset = curr_mouse_pos_ - prev_mouse_pos_;

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

    // convert spherical coordinates to cartesian coordinates
    const auto position = target + Vector3 {
        radius_ * std::sin(yaw_) * std::cos(pitch_),
        radius_ * std::sin(pitch_),
        radius_ * std::cos(yaw_) * std::cos(pitch_)
    };

    camera_->transform.SetPosition(position);
    camera_->LookAt(target);
}

auto OrbitControls::Orbit(const Vector2& offset, float delta) -> void {
    yaw_ -= offset.x * orbit_speed * delta;
    pitch_ += offset.y * orbit_speed * delta;
    pitch_ = std::clamp(pitch_, -kVerticalLimit, kVerticalLimit);
}

auto OrbitControls::Zoom(float scroll_offset, float delta) -> void {
    radius_ -= scroll_offset * zoom_speed * delta;
    radius_ = std::max(0.1f, radius_);
}

auto OrbitControls::Pan(const Vector2& offset, float delta) -> void {
    const auto forward = Normalize(camera_->transform.GetPosition() - target);
    const auto right = Normalize(Cross(forward, Vector3::Up()));
    const auto up = Cross(right, forward);

    const auto pan_h = right * (offset.x * pan_speed * delta);
    const auto pan_v = up * (offset.y * pan_speed * delta);

    target += pan_h + pan_v;
}

}