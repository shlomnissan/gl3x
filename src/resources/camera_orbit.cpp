// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/resources/camera_orbit.hpp"

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

auto CameraOrbit::Update(double delta) -> void {
    if (curr_mouse_button_ == MouseButton::Left) {
        // TODO: implement camera orbit
        prev_mouse_pos_ = curr_mouse_pos_;
    }
}

}