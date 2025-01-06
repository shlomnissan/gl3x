// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "renderer/gl/gl_state.hpp"

#include <glad/glad.h>

namespace engine {

auto GLState::ProcessMaterial(const Material* material) -> void {
    material->cull_backfaces ? Enable(GL_CULL_FACE) : Disable(GL_CULL_FACE);

    material->depth_test ? Enable(GL_DEPTH_TEST) : Disable(GL_DEPTH_TEST);

    if (material->polygon_offset) {
        Enable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(
            material->polygon_offset->factor,
            material->polygon_offset->units);
    } else {
        Disable(GL_POLYGON_OFFSET_FILL);
    }

    if (curr_invert_face_orientation_ != material->invert_face_orientation) {
        material->invert_face_orientation ? glFrontFace(GL_CW) : glFrontFace(GL_CCW);
        curr_invert_face_orientation_ = material->invert_face_orientation;
    }

    if (curr_wireframe_mode_ != material->wireframe) {
        material->wireframe
            ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
            : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        curr_wireframe_mode_ = material->wireframe;
    }
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

auto GLState::Reset() -> void {
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_POLYGON_OFFSET_FILL);

    glFrontFace(GL_CCW);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    features_.clear();

    curr_invert_face_orientation_ = false;
    curr_wireframe_mode_ = false;
}

}