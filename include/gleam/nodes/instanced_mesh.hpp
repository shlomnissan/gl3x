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
    std::size_t count;

    unsigned int instance_id = 0;

    bool touched {true};

    InstancedMesh(
        std::shared_ptr<Geometry> geometry,
        std::shared_ptr<Material> material,
        std::size_t count
    );

    [[nodiscard]] static auto Create(
        std::shared_ptr<Geometry> geometry,
        std::shared_ptr<Material> material,
        std::size_t count
    ) {
        return std::make_shared<InstancedMesh>(geometry, material, count);
    }

    [[nodiscard]] auto GetNodeType() const -> NodeType override {
        return NodeType::InstancedMeshNode;
    }

    [[nodiscard]] auto GetTransformAt(std::size_t idx) -> const Matrix4;

    auto SetTransformAt(std::size_t idx, const Matrix4& mat) -> void;

    auto SetTransformAt(std::size_t idx, Transform3& transform) -> void;

private:
    friend class GLBuffers;
    std::vector<Matrix4> transforms_;
};

}