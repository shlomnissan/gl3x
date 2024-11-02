// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "dinosaur.hpp"

#include <engine/geometry/plane_geometry.hpp>

Dinosaur::Dinosaur() : material_(engine::FlatMaterial::Create()) {
    material_->color = 0x628B48;
    mesh_ = engine::Mesh::Create(
        engine::PlaneGeometry::Create({.width = 44.0f, .height = 47.0f}),
        material_
    );

    mesh_->TranslateX(50.0f);
    mesh_->TranslateY(93.0f);

    Add(mesh_);
}

auto Dinosaur::Update(double delta) -> void {
    // TODO: handle updates
}

auto Dinosaur::OnKeyboardEvent(engine::KeyboardEvent* event) -> void {
    // TODO: handle keyboard events
}