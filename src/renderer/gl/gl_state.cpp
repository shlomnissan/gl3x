// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "renderer/gl/gl_state.hpp"

#include <glad/glad.h>

namespace engine {

auto GLState::ProcessMaterial(const Material* material) -> void {
    SetBackfaceCulling(!material->two_sided);
    SetDepthTest(material->depth_test);
    SetPolygonOffset(material->polygon_offset);
    SetWireframeMode(material->wireframe);
    SetBlending(!material->transparent ? Blending::None : material->blending);
}

auto GLState::Enable(int token) -> void {
    if (!features_.contains(token) || !features_[token]) {
        glEnable(token);
        features_[token] = true;
    }
}

auto GLState::Disable(int token) -> void {
    if (features_.contains(token) && features_[token]) {
        glDisable(token);
        features_[token] = false;
    }
}

auto GLState::SetBackfaceCulling(bool enabled) -> void {
    enabled ? Enable(GL_CULL_FACE) : Disable(GL_CULL_FACE);
}

auto GLState::SetDepthTest(bool enabled) -> void {
    enabled ? Enable(GL_DEPTH_TEST) : Disable(GL_DEPTH_TEST);
}

auto GLState::SetPolygonOffset(const std::optional<PolygonOffset>& polygon_offset) -> void {
    if (polygon_offset) {
        Enable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(polygon_offset->factor, polygon_offset->units);
    } else {
        Disable(GL_POLYGON_OFFSET_FILL);
    }
}

auto GLState::SetWireframeMode(bool enabled) -> void {
    if (curr_wireframe_mode_ != enabled) {
        enabled ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
                : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        curr_wireframe_mode_ = enabled;
    }
}

auto GLState::SetBlending(Blending blending) -> void {
    if (curr_blending_ != blending) {
        if (blending == Blending::None) {
            Disable(GL_BLEND);
        } else {
            Enable(GL_BLEND);
            switch (blending) {
            case Blending::Normal:
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                break;
            case Blending::Additive:
                glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                break;
            case Blending::Subtractive:
                glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
                break;
            case Blending::Multiply:
                glBlendFunc(GL_ZERO, GL_SRC_COLOR);
                break;
            case Blending::None:
                break;
            }
        }
        curr_blending_ = blending;
    }
}

auto GLState::SetClearColor(const Color& color) -> void {
    if (curr_clear_color_ != color) {
        glClearColor(color.r, color.g, color.b, 1.0f);
        curr_clear_color_ = color;
    }
}

auto GLState::Reset() -> void {
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    features_.clear();

    curr_wireframe_mode_ = false;
    curr_blending_ = Blending::None;
}

}