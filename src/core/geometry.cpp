// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/core/geometry.hpp"

#include <cassert>
#include <numeric>

namespace engine {

auto Geometry::SetAttribute(const GeometryAttribute &attribute) -> void {
    assert(attribute.item_size > 0);
    attributes_.emplace_back(attribute);
}

auto Geometry::VertexCount() const -> int {
    if (vertex_data_.empty() || attributes_.empty()) {
        return 0;
    }
    return vertex_data_.size() / Stride();
}

auto Geometry::Stride() const -> int {
    return std::accumulate(begin(attributes_), end(attributes_), 0,
        [](auto sum, const auto& attr){
            return sum + attr.item_size;
        }
    );
}

}