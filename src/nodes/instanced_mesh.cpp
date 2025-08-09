/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/instanced_mesh.hpp"

#include <cassert>

namespace gleam {

InstancedMesh::InstancedMesh(
    std::shared_ptr<Geometry> geometry,
    std::shared_ptr<Material> material,
    std::size_t count
): Mesh(geometry, material), count(count) {
    transforms_.resize(count);
    colors_.resize(count);
}

auto InstancedMesh::GetColorAt(std::size_t idx) -> const Color {
    assert(idx <= count);
    return colors_[idx];
}

auto InstancedMesh::GetTransformAt(std::size_t idx) -> const Matrix4 {
    assert(idx <= count);
    return transforms_[idx];
}

auto InstancedMesh::SetColorAt(std::size_t idx, const Color& color) -> void {
    assert(idx <= count);
    colors_[idx] = color;
    colors_touched = true;
}

auto InstancedMesh::SetTransformAt(std::size_t idx, const Matrix4& matrix) -> void {
    assert(idx <= count);
    transforms_[idx] = matrix;
    transforms_touched = true;
}

auto InstancedMesh::SetTransformAt(std::size_t idx, Transform3& transform) -> void {
    SetTransformAt(idx, transform.Get());
}

}