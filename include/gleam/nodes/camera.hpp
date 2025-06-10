/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/matrix4.hpp"
#include "gleam/nodes/node.hpp"

namespace gleam {

/**
 * @brief Represents available camera types.
 * @ingroup NodesGroup
 */
enum class CameraType {
    OrthographicCamera,
    PerspectiveCamera
};

/**
 * @brief **Abstract** base class for camera objects.
 *
 * It provides a common interface for all camera types. Not intended to be
 * instantiated directly.
 *
 * @ingroup NodesGroup
 */
class GLEAM_EXPORT Camera : public Node {
public:
    /// @brief Projection transform.
    Matrix4 projection_transform;

    /// @brief View transform.
    Matrix4 view_transform;

    /**
     * @brief Sets the view transform to the inverse of the node's world transform.
     */
    auto SetViewTransform() -> void;

    /**
     * @brief Returns camera type.
     *
     * @return CameraType
     */
    [[nodiscard]] virtual auto GetType() const -> CameraType = 0;

    /**
     * @brief Returns node type.
     *
     * @return NodeType::CameraNode
     */
    [[nodiscard]] auto GetNodeType() const -> NodeType override {
        return NodeType::CameraNode;
    }
};

}