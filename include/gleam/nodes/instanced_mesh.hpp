/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/nodes/mesh.hpp"
#include "gleam/math/color.hpp"
#include "gleam/math/matrix4.hpp"

#include <memory>
#include <vector>

namespace gleam {

class GLEAM_EXPORT InstancedMesh : public Mesh {
public:
    std::size_t count;

    unsigned int colors_buff_id = 0;

    unsigned int transforms_buff_id = 0;

    bool colors_touched {true};

    bool transforms_touched {true};

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

    [[nodiscard]] auto GetColorAt(std::size_t idx) -> const Color;

    [[nodiscard]] auto GetTransformAt(std::size_t idx) -> const Matrix4;

    auto SetColorAt(std::size_t idx, const Color& color) -> void;

    auto SetTransformAt(std::size_t idx, const Matrix4& matrix) -> void;

    auto SetTransformAt(std::size_t idx, Transform3& transform) -> void;

private:
    friend class GLBuffers;

    std::vector<Color> colors_;

    std::vector<Matrix4> transforms_;
};

}