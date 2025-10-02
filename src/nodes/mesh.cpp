/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gl3x/nodes/mesh.hpp"

#include "gl3x/geometries/wireframe_geometry.hpp"

namespace gl3x {

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