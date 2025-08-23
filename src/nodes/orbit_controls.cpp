/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/orbit_controls.hpp"

#include "gleam/math/spherical.hpp"
#include "gleam/math/vector2.hpp"
#include "gleam/math/vector3.hpp"

namespace gleam {

struct OrbitControls::Impl {
    Camera* camera;
    Spherical spherical {};
    Vector3 target = Vector3::Zero();
    Vector2 curr_pos {0.0f, 0.0f};
    Vector2 prev_pos {0.0f, 0.0f};
    MouseButton curr_button {MouseButton::None};
    float curr_scroll_offset {0.0f};

    auto OnUpdate(float delta, float orbit_speed, float pan_speed, float zoom_speed) {
        const auto offset = curr_pos - prev_pos;
        const auto do_orbit = curr_button == MouseButton::Left;
        const auto do_pan = curr_button == MouseButton::Right;
        const auto do_zoom = curr_scroll_offset != 0.0f;

        if (do_orbit) {
            spherical.phi -= offset.x * orbit_speed * delta;
            spherical.theta += offset.y * orbit_speed * delta;
        }

        if (do_zoom) {
            spherical.radius -= curr_scroll_offset * zoom_speed * delta;
            spherical.radius = std::max(0.1f, spherical.radius);
            curr_scroll_offset = 0.0f;
        }

        if (do_pan) {
            const auto& t = camera->view_transform;
            const auto right = Vector3 {t[0][0], t[1][0], t[2][0]};
            const auto up = Vector3 {t[0][1], t[1][1], t[2][1]};
            const auto speed = pan_speed * spherical.radius * delta;
            target -= (right * offset.x - up * offset.y) * speed;
        }

        prev_pos = curr_pos;

        spherical.MakeSafe();
        camera->transform.SetPosition(target + spherical.ToVector3());
        camera->LookAt(target);
    }
};

OrbitControls::OrbitControls(Camera* camera, const Parameters& params)
    : impl_(std::make_unique<Impl>())
{
    impl_->camera = camera;
    impl_->spherical.radius = params.radius;
    impl_->spherical.phi = params.yaw;
    impl_->spherical.theta = params.pitch;
};

auto OrbitControls::OnMouseEvent(MouseEvent* event) -> void {
    impl_->curr_pos = event->position;

    const auto is_pressed = event->type == MouseEvent::Type::ButtonPressed;
    if (is_pressed && impl_->curr_button == MouseButton::None) {
        impl_->curr_button = event->button;
    }

    const auto is_released = event->type == MouseEvent::Type::ButtonReleased;
    if (is_released && event->button == impl_->curr_button) {
        impl_->curr_button = MouseButton::None;
    }

    if (event->type == MouseEvent::Type::Scrolled) {
        impl_->curr_scroll_offset = event->scroll.y;
    }
}

auto OrbitControls::OnUpdate(float delta) -> void {
    impl_->OnUpdate(delta, orbit_speed, pan_speed, zoom_speed);
}

OrbitControls::~OrbitControls() = default;

}