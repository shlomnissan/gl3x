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
    int count
): Mesh(geometry, material), count(count) {
    transforms_.resize(count);
}

auto InstancedMesh::SetTransformAt(const Matrix4& mat, int idx) -> void {
    assert(idx <= count);
    transforms_[idx] = mat;
    touched = true;
}

auto InstancedMesh::SetTransformAt(Transform3& transform, int idx) -> void {
    SetTransformAt(transform.Get(), idx);
}

}