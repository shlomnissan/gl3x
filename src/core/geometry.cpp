// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/core/geometry.hpp"

#include <algorithm>
#include <cassert>
#include <numeric>

namespace engine {

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

}