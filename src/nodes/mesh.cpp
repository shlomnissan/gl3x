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

    auto v_min = Vector3 {std::numeric_limits<float>::max()};
    auto v_max = Vector3 {std::numeric_limits<float>::lowest()};

    const auto& vertex_data = geometry_->VertexData();
    const auto stride = geometry_->Stride();
    for (auto i = 0; i < vertex_data.size(); i += stride) {
        const auto x = vertex_data[i];
        const auto y = vertex_data[i + 1];
        const auto z = vertex_data[i + 2];

        v_min.x = std::min(v_min.x, x);
        v_min.y = std::min(v_min.y, y);
        v_min.z = std::min(v_min.z, z);
        v_max.x = std::max(v_max.x, x);
        v_max.y = std::max(v_max.y, y);
        v_max.z = std::max(v_max.z, z);
    }

    bounding_box = Box3 {v_min, v_max};
}

}