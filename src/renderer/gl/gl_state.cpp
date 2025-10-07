/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "renderer/gl/gl_state.hpp"

#include <glad/glad.h>

namespace vglx {

auto GLState::ProcessMaterial(const Material* material) -> void {
    SetBackfaceCulling(!material->two_sided);
    SetDepthTest(material->depth_test);
    SetPolygonOffset(material->polygon_offset_factor, material->polygon_offset_units);
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

auto GLState::SetViewport(int x, int y, int width, int height) const -> void {
    glViewport(x, y, width, height);
}

auto GLState::SetBackfaceCulling(bool enabled) -> void {
    enabled ? Enable(GL_CULL_FACE) : Disable(GL_CULL_FACE);
}

auto GLState::SetDepthTest(bool enabled) -> void {
    enabled ? Enable(GL_DEPTH_TEST) : Disable(GL_DEPTH_TEST);
}

auto GLState::SetDepthMask(bool enabled) -> void {
    if (curr_depth_mask_ != enabled) {
        glDepthMask(enabled ? GL_TRUE : GL_FALSE);
        curr_depth_mask_ = enabled;
    }
}

auto GLState::UseProgram(unsigned int program_id) -> void {
    if (curr_program_ != program_id) {
        glUseProgram(program_id);
        curr_program_ = program_id;
    }
}

auto GLState::SetPolygonOffset(float factor, float units) -> void {
    if (factor != 0.0f || units != 0.0f) {
        Enable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(factor, units);
    } else {
        Disable(GL_POLYGON_OFFSET_FILL);
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

    curr_blending_ = Blending::None;
    curr_depth_mask_ = false;
    curr_wireframe_mode_ = false;
    curr_program_ = 0;
}

}