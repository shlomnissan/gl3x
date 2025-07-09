/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/orbit_controls.hpp"

#include "gleam/math/utilities.hpp"
#include "gleam/math/vector2.hpp"
#include "gleam/math/vector3.hpp"

#include <algorithm>
#include <cmath>

namespace gleam {

constexpr auto kVerticalLimit = math::half_pi - 0.1f;

struct OrbitControls::Impl {
    Camera* camera;
    Vector3 target = Vector3::Zero();
    Vector2 curr_mouse_pos {0.0f, 0.0f};
    Vector2 prev_mouse_pos {0.0f, 0.0f};
    MouseButton curr_mouse_button {MouseButton::None};
    float radius;
    float pitch;
    float yaw;
    float curr_scroll_offset {0.0f};
    bool first_update {true};

    auto Orbit(const Vector2& offset, float delta, float orbit_speed) {
        yaw -= offset.x * orbit_speed * delta;
        pitch += offset.y * orbit_speed * delta;
        pitch = std::clamp(pitch, -kVerticalLimit, kVerticalLimit);
    }

    auto Zoom(float offset, float delta, float zoom_speed) {
        radius -= offset * zoom_speed * delta;
        radius = std::max(0.1f, radius);
    }

    auto Pan(const Vector2& offset, float delta, float pan_speed) {
        const auto forward = Normalize(camera->transform.GetPosition() - target);
        const auto right = Normalize(Cross(forward, Vector3::Up()));
        const auto up = Cross(right, forward);
        const auto pan_h = right * (offset.x * pan_speed * delta);
        const auto pan_v = up * (offset.y * pan_speed * delta);
        target += pan_h + pan_v;
    }

    auto OnUpdate(float delta, float orbit_speed, float pan_speed, float zoom_speed) {
        if (!first_update) {
            first_update = true;
            prev_mouse_pos = curr_mouse_pos;
            return;
        }

        const auto mouse_offset = curr_mouse_pos - prev_mouse_pos;

        if (curr_mouse_button == MouseButton::Left) {
            Orbit(mouse_offset, delta, orbit_speed);
        }

        if (curr_mouse_button == MouseButton::Right) {
            Pan(mouse_offset, delta, pan_speed);
        }

        if (curr_scroll_offset != 0.0f) {
            Zoom(curr_scroll_offset, delta, zoom_speed);
            curr_scroll_offset = 0.0f;
        }

        prev_mouse_pos = curr_mouse_pos;

        // convert spherical coordinates to cartesian coordinates
        const auto position = target + Vector3 {
            radius * std::sin(yaw) * std::cos(pitch),
            radius * std::sin(pitch),
            radius * std::cos(yaw) * std::cos(pitch)
        };

        camera->transform.SetPosition(position);
        camera->LookAt(target);
    }
};

OrbitControls::OrbitControls(Camera* camera, const Parameters& params)
    : impl_(std::make_unique<Impl>())
{
    impl_->camera = camera;
    impl_->radius = params.radius;
    impl_->pitch = params.pitch;
    impl_->yaw = params.yaw;
};

auto OrbitControls::OnMouseEvent(MouseEvent* event) -> void {
    using enum MouseButton;
    using enum MouseEvent::Type;

    impl_->curr_mouse_pos = event->position;

    if (event->type == ButtonPressed && impl_->curr_mouse_button == None) {
        impl_->curr_mouse_button = event->button;
    }

    if (event->type == ButtonReleased && event->button == impl_->curr_mouse_button) {
        impl_->curr_mouse_button = None;
    }

    if (event->type == Scrolled) {
        impl_->curr_scroll_offset = event->scroll.y;
    }
}

auto OrbitControls::OnUpdate(float delta) -> void {
    impl_->OnUpdate(delta, orbit_speed, pan_speed, zoom_speed);
}

OrbitControls::~OrbitControls() = default;

}