// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "gleam/core/geometry.hpp"

#include "utilities/logger.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>

namespace gleam {

auto Geometry::SetAttribute(const GeometryAttribute &attribute) -> void {
    assert(attribute.item_size > 0);
    attributes_.emplace_back(attribute);
}

auto Geometry::HasAttribute(GeometryAttributeType type) const -> bool {
    return std::ranges::any_of(attributes_, [type](const auto& attr){
        return attr.type == type;
    });
}

auto Geometry::VertexCount() const -> size_t {
    if (vertex_data_.empty() || attributes_.empty() || Stride() == 0) {
        return 0;
    }
    return vertex_data_.size() / Stride();
}

auto Geometry::Stride() const -> size_t {
    return std::accumulate(begin(attributes_), end(attributes_), 0,
        [](auto sum, const auto& attr){
            return sum + attr.item_size;
        }
    );
}

auto Geometry::BoundingBox() -> Box3 {
    if (!bounding_box_.has_value()) CreateBoundingBox();
    return bounding_box_.value();
}

auto Geometry::BoundingSphere() -> Sphere {
    if (!bounding_sphere_.has_value()) CreateBoundingSphere();
    return bounding_sphere_.value();
}

auto Geometry::CreateBoundingBox() -> void {
    using enum GeometryAttributeType;
    if (VertexCount() == 0 || !HasAttribute(Position)) {
        Logger::Log(LogLevel::Error, "Failed to create a bounding box");
        return;
    }

    bounding_box_ = Box3 {};
    auto stride = Stride();
    for (auto i = 0; i < vertex_data_.size(); i += stride) {
        bounding_box_->ExpandWithPoint({
            vertex_data_[i],
            vertex_data_[i + 1],
            vertex_data_[i + 2]
        });
    }
}

auto Geometry::CreateBoundingSphere() -> void {
    using enum GeometryAttributeType;
    if (VertexCount() == 0 || !HasAttribute(Position)) {
        Logger::Log(LogLevel::Error, "Failed to create a bounding sphere");
        return;
    }

    auto center = BoundingBox().Center();
    auto stride = Stride();
    auto max_distance_squared = 0.0f;
    for (auto i = 0; i < vertex_data_.size(); i += stride) {
        auto point = Vector3 {
            vertex_data_[i],
            vertex_data_[i + 1],
            vertex_data_[i + 2]
        };

        max_distance_squared = std::max(
            max_distance_squared,
            (center - point).LengthSquared()
        );
    }

    bounding_sphere_ = Sphere {center, std::sqrt(max_distance_squared)};
}

}