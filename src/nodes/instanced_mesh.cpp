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
}

auto InstancedMesh::GetTransformAt(std::size_t idx) -> const Matrix4 {
    assert(idx <= count);
    return transforms_[idx];
}

auto InstancedMesh::SetTransformAt(std::size_t idx, const Matrix4& mat) -> void {
    assert(idx <= count);
    transforms_[idx] = mat;
    touched = true;
}

auto InstancedMesh::SetTransformAt(std::size_t idx, Transform3& transform) -> void {
    SetTransformAt(idx, transform.Get());
}

}