/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/mesh.hpp"

#include "gleam/geometries/wireframe_geometry.hpp"

namespace gleam {

auto Mesh::SetGeometry(std::shared_ptr<Geometry> geometry) -> void {
    geometry_ = geometry;
    wireframe_geometry_ = nullptr;
}

auto Mesh::GetWireframeGeometry() -> std::shared_ptr<Geometry> {
    if (geometry_->primitive != GeometryPrimitiveType::Triangles) {
        return geometry_;
    }

    if (wireframe_geometry_ == nullptr) {
        wireframe_geometry_ = WireframeGeometry::Create(geometry_.get());
    }

    return wireframe_geometry_;
}

}