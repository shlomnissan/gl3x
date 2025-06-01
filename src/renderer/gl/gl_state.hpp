// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <gleam/materials/material.hpp>
#include <gleam/math/color.hpp>

#include <memory>
#include <unordered_map>

namespace engine {

class GLState {
public:
    auto ProcessMaterial(const std::shared_ptr<Material>& material) -> void;

    auto SetClearColor(const Color& color) -> void;

    auto SetDepthMask(bool enabled) -> void;

    auto SetViewport(int x, int y, int width, int height) const -> void;

    auto Reset() -> void;

private:
    std::unordered_map<int, bool> features_;

    Blending curr_blending_ {Blending::None};

    Color curr_clear_color_ {0.0f, 0.0f, 0.0f};

    bool curr_backface_culling_ {false};
    bool curr_depth_mask_ {false};
    bool curr_wireframe_mode_ {false};

    auto Enable(int token) -> void;

    auto Disable(int token) -> void;

    auto SetBackfaceCulling(bool enabled) -> void;

    auto SetDepthTest(bool enabled) -> void;

    auto SetPolygonOffset(const std::optional<PolygonOffset>& polygon_offset) -> void;

    auto SetWireframeMode(bool enabled) -> void;

    auto SetBlending(Blending blending) -> void;
};

}