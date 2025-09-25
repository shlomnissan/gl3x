/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/cameras/orthographic_camera.hpp"

namespace gleam {

namespace {

auto make_orthographic_proj(const OrthographicCamera::Parameters& params) {
    auto mat = Matrix4 {0.0f};
    mat[0] = {2.0f / (params.right - params.left), 0.0f, 0.0f, 0.0f};
    mat[1] = {0.0f, 2.0f / (params.top - params.bottom), 0.0f, 0.0f};
    mat[2] = {0.0f, 0.0f, -2.0f / (params.far - params.near), 0.0f};
    mat[3] = {
        -(params.right + params.left) / (params.right - params.left),
        -(params.top + params.bottom) / (params.top - params.bottom),
        -(params.far + params.near) / (params.far - params.near),
        1.0f
    };
    return mat;
}

}

OrthographicCamera::OrthographicCamera(const Parameters& params) : params_(params) {
    projection_matrix = make_orthographic_proj(params_);
}

auto OrthographicCamera::Resize(int width, int height) -> void {
    const auto fw = static_cast<float>(width);
    const auto fh = static_cast<float>(height);

    switch (resize_policy) {
    case ResizePolicy::PixelSpace: {
        params_.left = 0;
        params_.right = fw;
        params_.top = 0;
        params_.bottom = fh;
        break;
    }
    case ResizePolicy::FixedVertical: {
        const auto aspect = fw / fh;
        const auto center_x = 0.5f * (params_.left + params_.right);
        const auto center_y = 0.5f * (params_.top + params_.bottom);
        const auto half_v = 0.5f * (params_.top - params_.bottom);
        const auto half_h = half_v * aspect;

        params_.left = center_x - half_h;
        params_.right = center_x + half_h;
        params_.bottom = center_y - half_v;
        params_.top = center_y + half_v;
        break;
    }
    case ResizePolicy::FixedHorizontal: {
        const auto aspect = fw / fh;
        const auto center_x = 0.5f * (params_.left + params_.right);
        const auto center_y = 0.5f * (params_.top  + params_.bottom);
        const auto half_h = 0.5f * (params_.right - params_.left);
        const auto half_v = (aspect != 0.0f) ? (half_h / aspect) : 0.0f;

        params_.left   = center_x - half_h;
        params_.right  = center_x + half_h;
        params_.bottom = center_y - half_v;
        params_.top    = center_y + half_v;
        break;
    }};

    projection_matrix = make_orthographic_proj(params_);
}

}