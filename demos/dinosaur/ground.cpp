// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "ground.hpp"

#include <engine/geometry/plane_geometry.hpp>

Ground::Ground() : material_(engine::FlatMaterial::Create()) {
    material_->color = 0xDBB68F;
    mesh_ = engine::Mesh::Create(
        engine::PlaneGeometry::Create({.width = 600.0f, .height = 12.0f}),
        material_
    );

    mesh_->TranslateX(300.0f);
    mesh_->TranslateY(138.0f);

    Add(mesh_);
}

auto Ground::Update(double delta) -> void {
    // TODO: handle updates
}

auto Ground::OnKeyboardEvent(engine::KeyboardEvent* event) -> void {
    // TODO: handle keyboard events
}