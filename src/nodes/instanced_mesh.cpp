/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/instanced_mesh.hpp"

#include "nodes/instanced_mesh_impl.hpp"

#include <cassert>

namespace gleam {

InstancedMesh::InstancedMesh(
    std::shared_ptr<Geometry> geometry,
    std::shared_ptr<Material> material,
    std::size_t count
): Mesh(geometry, material), count_(count), impl_(std::make_unique<Impl>()) {
    transforms_.resize(count);
    colors_.resize(count);
}

auto InstancedMesh::GetColorAt(std::size_t idx) -> const Color {
    assert(idx <= count_);
    return colors_[idx];
}

auto InstancedMesh::GetTransformAt(std::size_t idx) -> const Matrix4 {
    assert(idx <= count_);
    return transforms_[idx];
}

auto InstancedMesh::SetColorAt(std::size_t idx, const Color& color) -> void {
    assert(idx <= count_);
    colors_[idx] = color;
    impl_->colors_touched = true;
}

auto InstancedMesh::SetTransformAt(std::size_t idx, const Matrix4& matrix) -> void {
    assert(idx <= count_);
    transforms_[idx] = matrix;
    impl_->transforms_touched = true;
}

auto InstancedMesh::SetTransformAt(std::size_t idx, Transform3& transform) -> void {
    SetTransformAt(idx, transform.Get());
}

auto InstancedMesh::BoundingSphere() -> Sphere {
    if (impl_->transforms_touched) {
        impl_->bounding_sphere.Reset();
        auto base = GetGeometry()->BoundingSphere();
        if (!base.IsEmpty() && count_ > 0) {
            for (auto i = 0; i < count_; ++i) {
                auto sphere = base;
                sphere.ApplyTransform(GetTransformAt(i));
                impl_->bounding_sphere.Union(sphere);
            }
        }
    }
    return impl_->bounding_sphere;
}

InstancedMesh::~InstancedMesh() = default;

}