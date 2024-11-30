// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/scene/mesh.hpp"
#include "engine/scene/node.hpp"

#include <memory>

namespace engine {

class ENGINE_EXPORT Grid : public Node {
public:
    explicit Grid(int dimensions);

    static auto Create(int dimensions) {
        return std::make_shared<Grid>(dimensions);
    }

private:
    std::shared_ptr<Mesh> mesh_;

    auto CreateGeometry(int dimensions) const -> std::shared_ptr<Geometry>;
};

}