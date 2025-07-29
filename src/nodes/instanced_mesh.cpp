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
): Mesh(geometry, material), count_(count) {
    matrices_.resize(count_);
}

auto InstancedMesh::SetMatrixAt(const Matrix4& mat, int idx) -> void {
    assert(idx <= count_);
    matrices_[idx] = mat;
    touched_ = true;
}

}