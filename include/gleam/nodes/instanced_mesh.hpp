/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/nodes/mesh.hpp"
#include "gleam/math/matrix4.hpp"

#include <memory>
#include <vector>

namespace gleam {

class GLEAM_EXPORT InstancedMesh : public Mesh {
public:
    InstancedMesh(
        std::shared_ptr<Geometry> geometry,
        std::shared_ptr<Material> material,
        int count
    );

    [[nodiscard]] static auto Create(
        std::shared_ptr<Geometry> geometry,
        std::shared_ptr<Material> material,
        int count
    ) {
        return std::make_shared<InstancedMesh>(geometry, material, count);
    }

    auto SetMatrixAt(const Matrix4& mat, int idx) -> void;

private:
    std::vector<Matrix4> matrices_;

    int count_;

    friend class Renderer;
    bool touched_ {true};
};

}