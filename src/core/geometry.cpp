// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/core/geometry.hpp"

#include <cassert>

namespace engine {

auto Geometry::SetAttribute(const GeometryAttribute &attribute) -> void {
    assert(attribute.item_size > 0);
    assert(attribute.offset < vertex_data_.size());
    attributes_.emplace_back(attribute);
}

auto Geometry::Dispose() -> void {
    // TODO: dispath dispose event
    disposed_ = true;
}

}