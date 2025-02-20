// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/core/geometry.hpp"
#include "engine/math/vector3.hpp"
#include "engine/nodes/mesh.hpp"

#include <limits>

namespace engine {

Mesh::Mesh(
    std::shared_ptr<Geometry> geometry,
    std::shared_ptr<Material> material
) : geometry_(geometry), material_(material) {}

auto Mesh::CreateBoundingBox() -> void {
    using enum GeometryAttributeType;
    if (geometry_->VertexCount() == 0 || !geometry_->HasAttribute(Position)) {
        return;
    }

    bounding_box = Box3 {};
    const auto& vertex_data = geometry_->VertexData();
    const auto stride = geometry_->Stride();
    for (auto i = 0; i < vertex_data.size(); i += stride) {
        bounding_box->ExpandWithPoint({
            vertex_data[i],
            vertex_data[i + 1],
            vertex_data[i + 2]
        });
    }
}

}