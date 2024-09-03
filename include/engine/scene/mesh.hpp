// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/core/geometry.hpp"
#include "engine/scene/node.hpp"

#include <memory>

namespace engine {

class Mesh : public Node {
public:
    explicit Mesh(std::shared_ptr<Geometry>& geometry);

private:
    std::shared_ptr<Geometry> geometry_;
};

}