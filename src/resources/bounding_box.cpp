// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/resources/bounding_box.hpp"

namespace engine {

BoundingBox::BoundingBox(const Box3& box) {
    CreateGeometry(box);
}

auto BoundingBox::CreateGeometry(const Box3& box) const -> std::shared_ptr<Geometry> {
    return Geometry::Create({});
}

}