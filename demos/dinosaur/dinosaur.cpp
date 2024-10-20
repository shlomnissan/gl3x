// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "dinosaur.hpp"

#include <engine/geometry/plane_geometry.hpp>

Dinosaur::Dinosaur() : material_(engine::FlatMaterial::Create()) {
    material_->color = 0x47A8BD;
    mesh_ = engine::Mesh::Create(
        engine::PlaneGeometry::Create({.width = 40.0f, .height = 40.0f}),
        material_
    );

    Add(mesh_);
}