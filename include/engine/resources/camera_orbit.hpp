// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/scene/node.hpp"
#include "engine/scene/camera_perspective.hpp"

#include "core/event.hpp"

#include <memory>

namespace engine {

/**
 * @brief A camera orbit node that allows the user to orbit around a target point.
 */
class ENGINE_EXPORT CameraOrbit : public Node {
public:
    /**
     * @brief Constructs a CameraOrbit object.
     *
     * @param camera A shared pointer to the camera to orbit around.
     */
    explicit CameraOrbit(const std::shared_ptr<CameraPerspective>& camera)
        : camera_(camera) {}


    /**
     * @brief Creates a new instance of the CameraOrbit class.
     *
     * @param camera A shared pointer to the camera to orbit around.
     * @return A `std::shared_ptr<CameraOrbit>` pointing to the newly created instance.
     */
    [[nodiscard]] static auto Create(const std::shared_ptr<CameraPerspective>& camera) {
        return std::make_shared<CameraOrbit>(camera);
    }

    /**
     * @brief Invoked when a mouse event is received.
     *
     * @param event A pointer to the mouse event.
     */
    auto OnMouseEvent(MouseEvent* event) -> void override;

    /**
     * @brief Invoked when the node is updated.
     *
     * @param delta The time in seconds since the last update.
     */
    auto Update(double delta) -> void override;

private:
    /// @brief The camera to orbit around.
    std::shared_ptr<CameraPerspective> camera_;
};

}